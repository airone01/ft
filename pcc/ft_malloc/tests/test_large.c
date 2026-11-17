#define _GNU_SOURCE /* mincore() */
#include "malloc.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define HDR(p) ((t_chunk_hdr *)((char *)(p) - CHUNK_HDR_SIZE))

/*
 * Large allocations: one zone (one mmap) per allocation, unmapped on free.
 * The zone starts ZONE_HDR_SIZE + CHUNK_HDR_SIZE bytes before the pointer.
 */
#define ZONE_OF(p) ((char *)(p) - CHUNK_HDR_SIZE - ZONE_HDR_SIZE)

static int failures;
static void run(const char *name, void (*fn)(void)) {
  fflush(stdout);
  pid_t pid = fork();
  if (pid == 0) {
    alarm(20);
    fn();
    _exit(0);
  }
  int st = 0;
  waitpid(pid, &st, 0);
  int ok = WIFEXITED(st) && WEXITSTATUS(st) == 0;
  printf("%s %s\n", ok ? "ok  " : "FAIL", name);
  if (!ok)
    failures++;
}
#define RUN(f) run(#f, f)

static void fill(void *p, size_t n, unsigned seed) {
  unsigned char *b = p;
  for (size_t i = 0; i < n; i++)
    b[i] = (unsigned char)(seed + i * 31u);
}
static int check(const void *p, size_t n, unsigned seed) {
  const unsigned char *b = p;
  for (size_t i = 0; i < n; i++)
    if (b[i] != (unsigned char)(seed + i * 31u))
      return 0;
  return 1;
}

static int mapped(const void *addr) {
  unsigned char v;
  uintptr_t mask = (uintptr_t)sysconf(_SC_PAGESIZE) - 1;
  return mincore((void *)((uintptr_t)addr & ~mask), 1, &v) == 0;
}
static int in_zone(int type, const void *p) {
  for (t_zone_hdr *z = alloc_conf.zones[type]; z; z = z->next)
    if ((const char *)p >= (const char *)z &&
        (const char *)p < (const char *)z + z->nmbytes)
      return 1;
  return 0;
}
static size_t zones(int type) {
  size_t n = 0;
  for (t_zone_hdr *z = alloc_conf.zones[type]; z; z = z->next)
    n++;
  return n;
}

/* ------------------------------------------------------------------ */

static void test_large_basic(void) {
  size_t n = 5000;
  unsigned char *p = malloc(n);
  assert(p != NULL);
  assert((uintptr_t)p % 16 == 0);
  assert(in_zone(Large, p));
  assert(HDR(p)->is_free == 0);
  assert(HDR(p)->nmbytes >= CHUNK_HDR_SIZE + n);
  fill(p, n, 3);
  assert(check(p, n, 3));
}

static void test_large_sizes(void) {
  size_t sizes[] = {
      1025, 4096, 5000, 65536, 100000, 1u << 20, (10u << 20) + 17};
  enum { N = sizeof sizes / sizeof *sizes };
  unsigned char *p[N];
  for (int i = 0; i < N; i++) {
    p[i] = malloc(sizes[i]);
    assert(p[i] != NULL);
    assert((uintptr_t)p[i] % 16 == 0);
    fill(p[i], sizes[i], (unsigned)i);
  }
  for (int i = 0; i < N; i++)
    assert(check(p[i], sizes[i], (unsigned)i));
}

static void test_one_zone_per_allocation(void) {
  size_t base = zones(Large);
  void *a = malloc(5000);
  void *b = malloc(5000);
  void *c = malloc(100000);
  assert(a && b && c);
  assert(zones(Large) == base + 3);
}

static void test_large_free_unmaps_the_zone(void) {
  size_t base = zones(Large);
  char *p = malloc(100000);
  assert(p != NULL);
  char *zone = ZONE_OF(p);
  assert(mapped(zone));
  assert(zones(Large) == base + 1);
  free(p);
  assert(zones(Large) == base);
  assert(!mapped(zone));
}

static void test_large_free_in_any_order(void) {
  size_t base = zones(Large);
  unsigned char *p[5];
  size_t n[5];
  for (int i = 0; i < 5; i++) {
    n[i] = 5000 + (size_t)i * 3000;
    p[i] = malloc(n[i]);
    assert(p[i] != NULL);
    fill(p[i], n[i], (unsigned)i);
  }
  int order[5] = {2, 0, 4, 1, 3};
  for (int k = 0; k < 5; k++) {
    char *zone = ZONE_OF(p[order[k]]);
    free(p[order[k]]);
    assert(!mapped(zone));
    for (int m = k + 1; m < 5; m++)
      assert(check(p[order[m]], n[order[m]], (unsigned)order[m]));
  }
  assert(zones(Large) == base);
}

static void test_large_overflow_sizes(void) {
  size_t base = zones(Large);
  size_t sizes[] = {SIZE_MAX,        SIZE_MAX - 1, SIZE_MAX - 4095,
                    SIZE_MAX - 4096, SIZE_MAX / 2, (size_t)1 << 62};
  for (size_t i = 0; i < sizeof sizes / sizeof *sizes; i++)
    assert(malloc(sizes[i]) == NULL);
  assert(zones(Large) == base);
}

static void test_huge_but_valid(void) {
  size_t n = 64u << 20; /* only touch both ends, pages are lazy */
  unsigned char *p = malloc(n);
  assert(p != NULL);
  p[0] = 1;
  p[n - 1] = 2;
  assert(p[0] == 1 && p[n - 1] == 2);
  free(p);
}

static void test_large_does_not_disturb_small(void) {
  unsigned char *a = malloc(300);
  unsigned char *l = malloc(50000);
  unsigned char *b = malloc(300);
  assert(a && l && b);
  fill(a, 300, 1);
  fill(l, 50000, 2);
  fill(b, 300, 3);
  free(l);
  assert(check(a, 300, 1));
  assert(check(b, 300, 3));
}

static void test_large_alloc_free_loop(void) {
  for (int i = 0; i < 200; i++) {
    char *p = malloc(1u << 20);
    assert(p != NULL);
    p[0] = p[(1u << 20) - 1] = 1;
    char *zone = ZONE_OF(p);
    free(p);
    assert(!mapped(zone));
  }
}

int main(void) {
  RUN(test_large_basic);
  RUN(test_large_sizes);
  RUN(test_one_zone_per_allocation);
  RUN(test_large_free_unmaps_the_zone);
  RUN(test_large_free_in_any_order);
  RUN(test_large_overflow_sizes);
  RUN(test_huge_but_valid);
  RUN(test_large_does_not_disturb_small);
  RUN(test_large_alloc_free_loop);
  return failures != 0;
}
