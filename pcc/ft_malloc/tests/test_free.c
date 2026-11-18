#define _GNU_SOURCE /* mincore() */
#include "malloc.h"
#include <assert.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
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
static int mapped(const void *addr) {
  unsigned char v;
  uintptr_t mask = (uintptr_t)sysconf(_SC_PAGESIZE) - 1;
  return mincore((void *)((uintptr_t)addr & ~mask), 1, &v) == 0;
}
static size_t zones(int type) {
  size_t n = 0;
  for (t_zone_hdr *z = _alloc_conf.zones[type]; z; z = z->next)
    n++;
  return n;
}
static int in_zone_ptr(const t_zone_hdr *z, const void *p) {
  return (const char *)p >= (const char *)z &&
         (const char *)p < (const char *)z + z->nmbytes;
}

/* g | a | b | c | h, all adjacent, all BLK bytes. g and h are guards. */
struct layout {
  void *g, *a, *b, *c, *h;
};
static struct layout make_layout(void) {
  struct layout l = {malloc(BLK), malloc(BLK), malloc(BLK), malloc(BLK),
                     malloc(BLK)};
  assert(l.g && l.a && l.b && l.c && l.h);
  assert(HDR(l.g)->next == HDR(l.a));
  assert(HDR(l.a)->next == HDR(l.b));
  assert(HDR(l.b)->next == HDR(l.c));
  assert(HDR(l.c)->next == HDR(l.h));
  return l;
}

/* ------------------------------------------------------------------ */

static void test_free_null(void) { free(NULL); }

static void test_invalid_pointers_are_ignored(void) {
  struct layout l = make_layout();
  fill(l.b, BLK, 5);
  int local;
  free(&local);
  free((void *)1);
  free((char *)l.b + 1);  /* inside a block */
  free((char *)l.b + 16); /* inside a block */
  free(HDR(l.b));         /* a header, not a payload */
  assert(HDR(l.b)->is_free == 0);
  assert(check(l.b, BLK, 5));
}

static void test_double_free_is_harmless(void) {
  struct layout l = make_layout();
  free(l.b);
  free(l.b);
  unsigned char *x = malloc(BLK);
  unsigned char *y = malloc(BLK);
  assert(x && y && x != y); /* never handed out twice */
  fill(x, BLK, 1);
  fill(y, BLK, 2);
  assert(check(x, BLK, 1));
  assert(check(y, BLK, 2));
}

/* b's header disappears in the merge: freeing b again must be ignored. */
static void test_double_free_after_merge(void) {
  struct layout l = make_layout();
  free(l.a);
  free(l.b);
  free(l.b);
  assert(HDR(l.a)->nmbytes == 2 * T);
  assert(malloc(1000) == l.a);
}

static void test_double_free_of_unmapped_large(void) {
  void *p = malloc(100000);
  assert(p != NULL);
  free(p);
  free(p); /* the zone is gone, must not be touched */
}

static void test_free_without_neighbours_does_not_merge(void) {
  struct layout l = make_layout();
  free(l.b);
  t_chunk_hdr *c = HDR(l.b);
  assert(c->is_free == 1);
  assert(c->nmbytes == T);
  assert(c->prev == HDR(l.a));
  assert(c->next == HDR(l.c));
}

static void test_coalesce_with_next(void) {
  struct layout l = make_layout();
  free(l.c);
  free(l.b); /* b absorbs c */
  t_chunk_hdr *b = HDR(l.b);
  assert(b->is_free);
  assert(b->nmbytes == 2 * T);
  assert(b->next == HDR(l.h));
  assert(HDR(l.h)->prev == b); /* back link updated */
  assert(b->prev == HDR(l.a));
}

static void test_coalesce_with_prev(void) {
  struct layout l = make_layout();
  free(l.a);
  free(l.b); /* a absorbs b */
  t_chunk_hdr *a = HDR(l.a);
  assert(a->is_free);
  assert(a->nmbytes == 2 * T);
  assert(a->next == HDR(l.c));
  assert(HDR(l.c)->prev == a);
}

static void test_coalesce_with_both(void) {
  struct layout l = make_layout();
  free(l.a);
  free(l.c);
  free(l.b); /* a absorbs b and c */
  t_chunk_hdr *a = HDR(l.a);
  assert(a->is_free);
  assert(a->nmbytes == 3 * T);
  assert(a->prev == HDR(l.g));
  assert(a->next == HDR(l.h));
  assert(HDR(l.h)->prev == a);
}

static void test_coalesce_with_zone_tail(void) {
  struct layout l = make_layout();
  assert(HDR(l.h)->next && HDR(l.h)->next->is_free);
  size_t before = HDR(l.h)->nmbytes;
  free(l.h); /* absorbs the free remainder at the end of the zone */
  assert(HDR(l.h)->is_free);
  assert(HDR(l.h)->next == NULL);
  assert(HDR(l.h)->nmbytes > before);
}

static void test_coalesce_at_start_of_zone(void) {
  struct layout l = make_layout();
  t_chunk_hdr *before = HDR(l.g)->prev; /* NULL, or something libc owns */
  free(l.a);
  free(l.g); /* g absorbs a */
  t_chunk_hdr *g = HDR(l.g);
  assert(g->is_free);
  assert(g->prev == before);
  assert(g->nmbytes == 2 * T);
  assert(g->next == HDR(l.b));
  assert(HDR(l.b)->prev == g);
}

static void test_merged_chunk_is_reusable(void) {
  struct layout l = make_layout();
  free(l.a);
  free(l.b);
  free(l.c);
  void *p = malloc(1000);
  assert(p == l.a);
  fill(p, 1000, 7);
  assert(check(p, 1000, 7));
}

static void test_free_does_not_touch_neighbours(void) {
  struct layout l = make_layout();
  void *all[5] = {l.g, l.a, l.b, l.c, l.h};
  for (int i = 0; i < 5; i++)
    fill(all[i], BLK, (unsigned)i);
  free(l.a);
  free(l.c);
  assert(check(l.g, BLK, 0));
  assert(check(l.b, BLK, 2));
  assert(check(l.h, BLK, 4));
}

/* All 120 orders in which 5 blocks of mixed sizes can be freed. */
static void free_in_order(const int *order) {
  size_t sz[5] = {16, 48, 200, 512, 1000};
  void *p[5];
  for (int i = 0; i < 5; i++) {
    p[i] = malloc(sz[i]);
    assert(p[i] != NULL);
    fill(p[i], sz[i], (unsigned)i);
  }
  for (int k = 0; k < 5; k++) {
    free(p[order[k]]);
    for (int m = k + 1; m < 5; m++)
      assert(check(p[order[m]], sz[order[m]], (unsigned)order[m]));
  }
}
static void permute(int *o, int k) {
  if (k == 5) {
    free_in_order(o);
    return;
  }
  for (int i = k; i < 5; i++) {
    int t = o[k];
    o[k] = o[i];
    o[i] = t;
    permute(o, k + 1);
    t = o[k];
    o[k] = o[i];
    o[i] = t;
  }
}
static void test_free_in_every_order(void) {
  int order[5] = {0, 1, 2, 3, 4};
  permute(order, 0);
}

/* ---- zone release ---- */

/* Allocates BLK blocks until the Small list has at least 'want' zones. */
static int fill_zones(void **ptr, size_t want) {
  int n = 0;
  while (zones(Small) < want) {
    ptr[n] = malloc(BLK);
    assert(ptr[n] != NULL);
    fill(ptr[n], BLK, (unsigned)n);
    n++;
  }
  return n;
}

/* A zone that is completely free again is given back to the kernel. */
static void test_empty_last_zone_is_unmapped(void) {
  void *keep = malloc(BLK);
  assert(keep != NULL);
  size_t base = zones(Small);
  void *ptr[1000];
  int n = fill_zones(ptr, base + 1);

  t_zone_hdr *last = _alloc_conf.zones[Small];
  while (last->next)
    last = last->next;
  char *start = (char *)last;

  for (int i = 0; i < n; i++)
    if (in_zone_ptr(last, ptr[i]))
      free(ptr[i]);

  assert(zones(Small) == base);
  assert(!mapped(start));
}

/* Releasing a zone in the middle must relink its neighbours. */
static void test_release_middle_zone(void) {
  void *ptr[1000];
  int n = fill_zones(ptr, zones(Small) + 3);
  size_t base = zones(Small);
  t_zone_hdr *first = _alloc_conf.zones[Small];
  t_zone_hdr *mid = first->next;
  t_zone_hdr *after = mid->next;
  assert(after != NULL);

  char in_mid[1000];
  for (int i = 0; i < n; i++)
    in_mid[i] = in_zone_ptr(mid, ptr[i]);
  for (int i = 0; i < n; i++)
    if (in_mid[i])
      free(ptr[i]);

  assert(zones(Small) == base - 1);
  assert(first->next == after);
  assert(after->prev == first);
  for (int i = 0; i < n; i++)
    if (!in_mid[i])
      assert(check(ptr[i], BLK, (unsigned)i));
}

/* Releasing the head zone must keep the rest of the list reachable. */
static void test_release_head_zone(void) {
  void *ptr[1000];
  int n = fill_zones(ptr, zones(Small) + 2);
  size_t base = zones(Small);
  t_zone_hdr *head = _alloc_conf.zones[Small];

  /* Skip if libc itself owns a block in the head zone: it can't be freed. */
  size_t used = 0, ours = 0;
  for (t_chunk_hdr *c = head->chunk; c; c = c->next)
    if (!c->is_free)
      used++;
  for (int i = 0; i < n; i++)
    if (in_zone_ptr(head, ptr[i]))
      ours++;
  if (used != ours)
    return;

  char in_head[1000];
  for (int i = 0; i < n; i++)
    in_head[i] = in_zone_ptr(head, ptr[i]);
  for (int i = 0; i < n; i++)
    if (in_head[i])
      free(ptr[i]);

  assert(zones(Small) == base - 1);
  assert(_alloc_conf.zones[Small] != head);
  assert(_alloc_conf.zones[Small] != NULL);
  assert(_alloc_conf.zones[Small]->prev == NULL);
  for (int i = 0; i < n; i++)
    if (!in_head[i])
      assert(check(ptr[i], BLK, (unsigned)i));
}

/* Freeing everything leaves at most one zone per class (no thrashing). */
static void test_free_everything_leaves_at_most_one_zone(void) {
  size_t large = zones(Large);
  enum { N = 1500 };
  static void *p[N];
  for (int i = 0; i < N; i++) {
    p[i] = malloc(16 + (size_t)(i % 80) * 16);
    assert(p[i] != NULL);
  }
  for (int i = 0; i < N; i++)
    free(p[i]);
  assert(zones(Tiny) <= 1);
  assert(zones(Small) <= 1);
  assert(zones(Large) == large);
}

static void test_free_preserves_errno(void) {
  struct layout l = make_layout();
  void *big = malloc(100000);
  assert(big != NULL);
  int local;
  errno = EDOM;
  free(NULL);
  free(&local);
  free(l.b);
  free(big); /* munmap path */
  assert(errno == EDOM);
}

int main(void) {
  RUN(test_free_null);
  RUN(test_invalid_pointers_are_ignored);
  RUN(test_double_free_is_harmless);
  RUN(test_double_free_after_merge);
  RUN(test_double_free_of_unmapped_large);
  RUN(test_free_without_neighbours_does_not_merge);
  RUN(test_coalesce_with_next);
  RUN(test_coalesce_with_prev);
  RUN(test_coalesce_with_both);
  RUN(test_coalesce_with_zone_tail);
  RUN(test_coalesce_at_start_of_zone);
  RUN(test_merged_chunk_is_reusable);
  RUN(test_free_does_not_touch_neighbours);
  RUN(test_free_in_every_order);
  RUN(test_empty_last_zone_is_unmapped);
  RUN(test_release_middle_zone);
  RUN(test_release_head_zone);
  RUN(test_free_everything_leaves_at_most_one_zone);
  RUN(test_free_preserves_errno);
  return failures != 0;
}
