#include "malloc.h"
#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define HDR(p) ((t_chunk_hdr *)((char *)(p) - CHUNK_HDR_SIZE))
#define BLK 512

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

/* ------------------------------------------------------------------ */

/* malloc(0) may return NULL or a unique pointer, but must not break. */
static void test_zero_size(void) {
  void *p = malloc(0);
  free(p);
  assert(malloc(16) != NULL);
}

/* Sizes where ALIGN16 / header addition / page rounding would wrap. */
static void test_huge_sizes_return_null(void) {
  size_t sizes[] = {SIZE_MAX,        SIZE_MAX - 1,  SIZE_MAX - 15,
                    SIZE_MAX - 16,   SIZE_MAX - 31, SIZE_MAX - 4095,
                    SIZE_MAX - 4096, SIZE_MAX / 2,  SIZE_MAX / 2 + 1};
  for (size_t i = 0; i < sizeof sizes / sizeof *sizes; i++)
    assert(malloc(sizes[i]) == NULL);
  assert(malloc(16) != NULL); /* still usable afterwards */
}

static void test_failure_sets_errno(void) {
  errno = 0;
  assert(malloc(SIZE_MAX) == NULL);
  assert(errno == ENOMEM);
}

static void test_failed_alloc_does_not_corrupt(void) {
  unsigned char *a = malloc(BLK);
  assert(a != NULL);
  fill(a, BLK, 9);
  assert(malloc(SIZE_MAX) == NULL);
  assert(check(a, BLK, 9));
  void *b = malloc(BLK);
  assert(b != NULL && b != (void *)a);
}

/* Every size within +-17 of the Tiny and Small limits. */
static void test_boundary_sizes(void) {
  size_t page = (size_t)sysconf(_SC_PAGESIZE);
  size_t bases[2] = {page / 32, page / 4};
  static unsigned char *p[80];
  static size_t n[80];
  int cnt = 0;
  for (int b = 0; b < 2; b++) {
    for (int d = -17; d <= 17; d++) {
      n[cnt] = (size_t)((long)bases[b] + d);
      p[cnt] = malloc(n[cnt]);
      assert(p[cnt] != NULL);
      assert((uintptr_t)p[cnt] % 16 == 0);
      fill(p[cnt], n[cnt], (unsigned)cnt);
      cnt++;
    }
  }
  for (int i = 0; i < cnt; i++)
    assert(check(p[i], n[i], (unsigned)i));
}

static void test_every_size_up_to_small_limit(void) {
  size_t small = (size_t)sysconf(_SC_PAGESIZE) / 4;
  static unsigned char *p[4096];
  assert(small < 4096);
  for (size_t n = 1; n <= small; n++) {
    p[n] = malloc(n);
    assert(p[n] != NULL);
    fill(p[n], n, (unsigned)n);
  }
  for (size_t n = 1; n <= small; n++)
    assert(check(p[n], n, (unsigned)n));
}

/*
 * g | a(free) | h. Asking for a bit less than a's size must hand out a
 * chunk that is marked used and never gets handed out twice.
 */
static void reuse_case(size_t request, size_t expected_chunk_size) {
  void *g = malloc(BLK);
  void *a = malloc(BLK);
  void *h = malloc(BLK);
  assert(g && a && h);
  assert(HDR(a)->next == HDR(h));
  free(a);

  void *p = malloc(request);
  assert(p == a); /* first fit */
  assert(HDR(p)->is_free == 0);
  assert(HDR(p)->nmbytes == expected_chunk_size);

  void *q = malloc(request);
  assert(q != NULL && q != p);
  fill(p, request, 1);
  fill(q, request, 2);
  assert(check(p, request, 1));
  assert(check(q, request, 2));
}

/* exact fit: no remainder, no split */
static void test_exact_fit(void) { reuse_case(BLK, CHUNK_HDR_SIZE + BLK); }

/* remainder of 16 bytes is too small for header + MIN_PAYLOAD: no split */
static void test_remainder_too_small_to_split(void) {
  reuse_case(BLK - 16, CHUNK_HDR_SIZE + BLK);
}

/* remainder is exactly header + MIN_PAYLOAD: smallest legal split */
static void test_smallest_legal_split(void) {
  size_t rem = CHUNK_HDR_SIZE + MIN_PAYLOAD;
  reuse_case(BLK - rem, CHUNK_HDR_SIZE + BLK - rem);
}

int main(void) {
  RUN(test_zero_size);
  RUN(test_huge_sizes_return_null);
  RUN(test_failure_sets_errno);
  RUN(test_failed_alloc_does_not_corrupt);
  RUN(test_boundary_sizes);
  RUN(test_every_size_up_to_small_limit);
  RUN(test_exact_fit);
  RUN(test_remainder_too_small_to_split);
  RUN(test_smallest_legal_split);
  return failures != 0;
}
