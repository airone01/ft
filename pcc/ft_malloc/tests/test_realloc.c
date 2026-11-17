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
#define T (CHUNK_HDR_SIZE + BLK) /* size of one block, header included */

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
static size_t round16(size_t n) { return (n + 15) & ~(size_t)15; }

/* ---- contract ---- */

static void test_null_pointer_is_malloc(void) {
  unsigned char *p = realloc(NULL, 100);
  assert(p != NULL);
  assert((uintptr_t)p % 16 == 0);
  fill(p, 100, 1);
  assert(check(p, 100, 1));
}

/* realloc(p, 0) releases p; it may return NULL or a unique pointer. */
static void test_zero_size(void) {
  void *p = malloc(32);
  assert(p != NULL);
  void *r = realloc(p, 0);
  free(r);
  assert(malloc(16) != NULL);
}

static void test_invalid_pointer_returns_null(void) {
  unsigned char *p = malloc(64);
  assert(p != NULL);
  fill(p, 64, 4);
  int local;
  assert(realloc(&local, 10) == NULL);
  assert(realloc(p + 1, 10) == NULL);
  assert(HDR(p)->is_free == 0);
  assert(check(p, 64, 4));
}

static void test_failure_keeps_the_original(void) {
  unsigned char *p = malloc(64);
  assert(p != NULL);
  fill(p, 64, 8);
  errno = 0;
  assert(realloc(p, SIZE_MAX) == NULL);
  assert(errno == ENOMEM);
  assert(HDR(p)->is_free == 0);
  assert(check(p, 64, 8));
}

/* ---- same size / shrinking ---- */

static void test_same_size_keeps_the_pointer(void) {
  void *p = malloc(100);
  assert(p != NULL);
  assert(realloc(p, 100) == p);
  assert(realloc(p, 99) == p);
  assert(realloc(p, round16(100)) == p);
}

static void test_shrink_splits_in_place(void) {
  unsigned char *p = malloc(BLK);
  void *h = malloc(BLK);
  assert(p && h);
  assert(HDR(p)->next == HDR(h));
  fill(p, BLK, 1);

  unsigned char *r = realloc(p, 300);
  assert(r == p);
  assert(check(r, 300, 1));

  size_t used = CHUNK_HDR_SIZE + round16(300);
  t_chunk_hdr *c = HDR(r);
  assert(c->nmbytes == used);
  assert(c->next != NULL && c->next->is_free);
  assert((char *)c->next == (char *)c + used);
  assert(c->next->nmbytes == T - used);
  assert(c->next->next == HDR(h));
  assert(HDR(h)->prev == c->next);
}

/* remainder of 16 bytes is too small for a chunk: nothing is split off */
static void test_shrink_by_a_few_bytes_does_not_split(void) {
  void *p = malloc(BLK);
  void *h = malloc(BLK);
  assert(p && h);
  void *r = realloc(p, BLK - 16);
  assert(r == p);
  assert(HDR(r)->nmbytes == T);
  assert(HDR(r)->next == HDR(h));
}

/* The chunk cut off by a shrink must merge with a free next chunk. */
static void test_shrink_merges_tail_with_free_next(void) {
  void *p = malloc(BLK);
  void *n = malloc(BLK);
  void *h = malloc(BLK);
  assert(p && n && h);
  free(n);
  void *r = realloc(p, 100);
  assert(r == p);
  t_chunk_hdr *c = HDR(r);
  assert(c->next && c->next->is_free);
  assert(c->next->nmbytes == T + (T - (CHUNK_HDR_SIZE + round16(100))));
  assert(c->next->next == HDR(h));
  assert(HDR(h)->prev == c->next);
}

/* ---- growing ---- */

static void test_grow_in_place_into_free_next(void) {
  unsigned char *a = malloc(BLK);
  void *b = malloc(BLK);
  void *h = malloc(BLK);
  assert(a && b && h);
  assert(HDR(a)->next == HDR(b));
  fill(a, BLK, 2);
  free(b);

  unsigned char *r = realloc(a, 800);
  assert(r == a);
  assert(check(r, BLK, 2));
  size_t need = CHUNK_HDR_SIZE + round16(800);
  t_chunk_hdr *c = HDR(r);
  assert(c->nmbytes == need);
  assert(c->next && c->next->is_free);
  assert(c->next->nmbytes == 2 * T - need);
  assert(c->next->next == HDR(h));
}

/* Spare room of 32 bytes can't hold a chunk: it must be absorbed. */
static void test_grow_absorbs_unsplittable_remainder(void) {
  void *a = malloc(BLK);
  void *b = malloc(BLK);
  void *h = malloc(BLK);
  assert(a && b && h);
  free(b);
  void *r = realloc(a, 1024);
  assert(r == a);
  assert(HDR(r)->nmbytes == 2 * T);
  assert(HDR(r)->next == HDR(h));
  assert(HDR(h)->prev == HDR(r));
}

static void test_grow_into_zone_tail(void) {
  unsigned char *p = malloc(BLK);
  assert(p != NULL);
  assert(HDR(p)->next && HDR(p)->next->is_free);
  fill(p, BLK, 6);
  unsigned char *r = realloc(p, 900);
  assert(r == p);
  assert(check(r, BLK, 6));
  assert(HDR(r)->nmbytes == CHUNK_HDR_SIZE + round16(900));
}

static void test_grow_moves_when_blocked(void) {
  void *g = malloc(BLK);
  unsigned char *a = malloc(BLK);
  void *b = malloc(BLK);
  void *h = malloc(BLK);
  assert(g && a && b && h);
  fill(g, BLK, 1);
  fill(a, BLK, 2);
  fill(b, BLK, 3);
  fill(h, BLK, 4);

  unsigned char *r = realloc(a, 800);
  assert(r != NULL && r != a);
  assert(check(r, BLK, 2));
  assert(check(g, BLK, 1));
  assert(check(b, BLK, 3));
  assert(check(h, BLK, 4));
  assert(HDR(a)->is_free == 1); /* old block was released */
}

/* ---- classes and data ---- */

static void test_data_survives_class_changes(void) {
  size_t chain[] = {10, 300, 5000, 300, 10, 70000, 200};
  size_t cur = chain[0];
  unsigned char *p = malloc(cur);
  assert(p != NULL);
  fill(p, cur, 5);
  for (size_t i = 1; i < sizeof chain / sizeof *chain; i++) {
    size_t n = chain[i];
    p = realloc(p, n);
    assert(p != NULL);
    assert(check(p, cur < n ? cur : n, 5));
    cur = n;
    fill(p, cur, 5);
  }
}

static void test_all_size_pairs(void) {
  size_t sz[] = {1, 15, 16, 17, 100, 128, 129, 500, 1024, 1025, 3000, 70000};
  enum { N = sizeof sz / sizeof *sz };
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      unsigned char *p = malloc(sz[i]);
      assert(p != NULL);
      fill(p, sz[i], 7);
      unsigned char *r = realloc(p, sz[j]);
      assert(r != NULL);
      assert((uintptr_t)r % 16 == 0);
      assert(check(r, sz[i] < sz[j] ? sz[i] : sz[j], 7));
      fill(r, sz[j], 9); /* the whole new size must be writable */
      assert(check(r, sz[j], 9));
      free(r);
    }
  }
}

static void test_large_grow_and_shrink(void) {
  unsigned char *p = malloc(100000);
  assert(p != NULL);
  fill(p, 100000, 3);
  p = realloc(p, 300000);
  assert(p != NULL);
  assert(check(p, 100000, 3));
  p = realloc(p, 10);
  assert(p != NULL);
  assert(check(p, 10, 3));
  free(p);
}

/* ---- many steps ---- */

static void test_grow_one_byte_at_a_time(void) {
  unsigned char *p = NULL;
  for (size_t n = 1; n <= 2500; n++) {
    p = realloc(p, n);
    assert(p != NULL);
    assert(check(p, n - 1, 1)); /* everything written so far */
    p[n - 1] = (unsigned char)(1 + (n - 1) * 31u);
  }
  assert(check(p, 2500, 1));
}

static void test_shrink_in_steps(void) {
  size_t n = 3000;
  unsigned char *p = malloc(n);
  assert(p != NULL);
  fill(p, n, 2);
  while (n > 8) {
    n -= 7;
    p = realloc(p, n);
    assert(p != NULL);
    assert(check(p, n, 2));
  }
}

static void test_never_touches_neighbours(void) {
  unsigned char *a = malloc(BLK);
  unsigned char *b = malloc(BLK);
  unsigned char *c = malloc(BLK);
  assert(a && b && c);
  fill(a, BLK, 1);
  fill(b, BLK, 2);
  fill(c, BLK, 3);
  size_t sizes[] = {10, 700, 100, 1024, 2000, 300, 5000, 20};
  size_t cur = BLK;
  for (size_t i = 0; i < sizeof sizes / sizeof *sizes; i++) {
    b = realloc(b, sizes[i]);
    assert(b != NULL);
    assert(check(b, cur < sizes[i] ? cur : sizes[i], 2));
    cur = sizes[i];
    fill(b, cur, 2);
    assert(check(a, BLK, 1));
    assert(check(c, BLK, 3));
  }
}

int main(void) {
  RUN(test_null_pointer_is_malloc);
  RUN(test_zero_size);
  RUN(test_invalid_pointer_returns_null);
  RUN(test_failure_keeps_the_original);
  RUN(test_same_size_keeps_the_pointer);
  RUN(test_shrink_splits_in_place);
  RUN(test_shrink_by_a_few_bytes_does_not_split);
  RUN(test_shrink_merges_tail_with_free_next);
  RUN(test_grow_in_place_into_free_next);
  RUN(test_grow_absorbs_unsplittable_remainder);
  RUN(test_grow_into_zone_tail);
  RUN(test_grow_moves_when_blocked);
  RUN(test_data_survives_class_changes);
  RUN(test_all_size_pairs);
  RUN(test_large_grow_and_shrink);
  RUN(test_grow_one_byte_at_a_time);
  RUN(test_shrink_in_steps);
  RUN(test_never_touches_neighbours);
  return failures != 0;
}
