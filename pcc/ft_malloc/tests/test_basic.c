#include "malloc.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define HDR(p) ((t_chunk_hdr *)((char *)(p) - CHUNK_HDR_SIZE))
#define BLK 512

/* Each test runs in its own process so heap state never leaks between them. */
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

static void test_non_null_and_aligned(void) {
  for (size_t n = 1; n <= 2048; n++) {
    void *p = malloc(n);
    assert(p != NULL);
    assert((uintptr_t)p % 16 == 0);
  }
}

static void test_memory_is_writable(void) {
  size_t sizes[] = {1, 7, 16, 100, 128, 129, 500, 1024, 1025, 5000};
  enum { N = sizeof sizes / sizeof *sizes };
  void *p[N];
  for (int i = 0; i < N; i++) {
    p[i] = malloc(sizes[i]);
    assert(p[i] != NULL);
    fill(p[i], sizes[i], (unsigned)i);
  }
  for (int i = 0; i < N; i++)
    assert(check(p[i], sizes[i], (unsigned)i)); /* nothing overlaps */
}

/* nmbytes is the full chunk size, header included, and a multiple of 16. */
static void test_header_fields(void) {
  char *p = malloc(4);
  assert(p != NULL);
  t_chunk_hdr *c = HDR(p);
  assert(c->is_free == 0);
  assert(c->nmbytes % 16 == 0);
  assert(c->nmbytes >= CHUNK_HDR_SIZE + 16);
  if (c->next && c->next->is_free) { /* came from a split: exact size */
    assert(c->nmbytes == CHUNK_HDR_SIZE + 16);
  }
}

static void test_split_structure(void) {
  void *p = malloc(BLK);
  assert(p != NULL);
  t_chunk_hdr *c = HDR(p);
  assert(c->nmbytes == CHUNK_HDR_SIZE + BLK);
  assert(c->next != NULL);
  assert(c->next->is_free == 1);
  assert((char *)c->next == (char *)c + c->nmbytes);
  assert(c->next->prev == c);
}

static void test_size_classes(void) {
  size_t page = (size_t)sysconf(_SC_PAGESIZE);
  size_t tiny = page / 32, small = page / 4;
  assert(in_zone(Tiny, malloc(1)));
  assert(in_zone(Tiny, malloc(tiny)));
  assert(in_zone(Small, malloc(tiny + 1)));
  assert(in_zone(Small, malloc(small)));
  assert(in_zone(Large, malloc(small + 1)));
}

static void test_many_allocations_keep_their_data(void) {
  enum { N = 1000 };
  static unsigned char *p[N];
  for (int i = 0; i < N; i++) {
    p[i] = malloc(100);
    assert(p[i] != NULL);
    fill(p[i], 100, (unsigned)i);
  }
  for (int i = 0; i < N; i++)
    assert(check(p[i], 100, (unsigned)i));
}

static void test_spills_into_new_zone(void) {
  enum { N = 400 };
  static void *p[N];
  size_t before = zones(Small);
  for (int i = 0; i < N; i++) {
    p[i] = malloc(BLK);
    assert(p[i] != NULL);
  }
  assert(zones(Small) >= before + 1);
  for (int i = 0; i < N; i++) {
    t_zone_hdr *z = NULL; /* every chunk lies inside some zone */
    for (z = alloc_conf.zones[Small]; z; z = z->next)
      if ((char *)p[i] > (char *)z && (char *)p[i] < (char *)z + z->nmbytes)
        break;
    assert(z != NULL);
  }
}

/* The freed slot is the first fit, so it must come back. */
static void test_freed_slot_is_reused(void) {
  void *keep = malloc(BLK);
  void *a = malloc(BLK);
  assert(keep && a);
  free(a);
  void *b = malloc(BLK);
  assert(b == a);
}

int main(void) {
  RUN(test_non_null_and_aligned);
  RUN(test_memory_is_writable);
  RUN(test_header_fields);
  RUN(test_split_structure);
  RUN(test_size_classes);
  RUN(test_many_allocations_keep_their_data);
  RUN(test_spills_into_new_zone);
  RUN(test_freed_slot_is_reused);
  return failures != 0;
}
