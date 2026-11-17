#include "malloc.h"
#include <assert.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

static int failures;
static void run(const char *name, void (*fn)(void)) {
  fflush(stdout);
  pid_t pid = fork();
  if (pid == 0) {
    alarm(30);
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
static size_t zones(int type) {
  size_t n = 0;
  for (t_zone_hdr *z = alloc_conf.zones[type]; z; z = z->next)
    n++;
  return n;
}

static uint64_t rng;
static uint64_t rnd(void) {
  rng ^= rng << 13;
  rng ^= rng >> 7;
  rng ^= rng << 17;
  return rng;
}
static size_t rand_size(void) {
  uint64_t r = rnd() % 100;
  if (r < 60)
    return 1 + rnd() % 200;
  if (r < 90)
    return 1 + rnd() % 1024;
  if (r < 99)
    return 1025 + rnd() % 8000;
  return 20000 + rnd() % 200000;
}

/* ------------------------------------------------------------------ */

#define SLOTS 512
static struct {
  unsigned char *p;
  size_t n;
  unsigned seed;
} slots[SLOTS];

/* Random malloc / free / realloc, verifying contents on every access. Any
 * overlap or lost data shows up as a pattern mismatch. */
static void random_run(uint64_t seed, int ops) {
  size_t large = zones(Large);
  rng = seed;
  memset(slots, 0, sizeof slots);

  for (int op = 0; op < ops; op++) {
    size_t i = rnd() % SLOTS;
    if (!slots[i].p) {
      slots[i].n = rand_size();
      slots[i].p = malloc(slots[i].n);
      assert(slots[i].p != NULL);
      assert((uintptr_t)slots[i].p % 16 == 0);
      slots[i].seed = (unsigned)rnd();
      fill(slots[i].p, slots[i].n, slots[i].seed);
      continue;
    }
    assert(check(slots[i].p, slots[i].n, slots[i].seed));
    switch (rnd() % 3) {
    case 0:
      free(slots[i].p);
      slots[i].p = NULL;
      break;
    case 1: {
      size_t n = rand_size();
      unsigned char *q = realloc(slots[i].p, n);
      assert(q != NULL);
      assert(check(q, n < slots[i].n ? n : slots[i].n, slots[i].seed));
      slots[i].p = q;
      slots[i].n = n;
      slots[i].seed = (unsigned)rnd();
      fill(q, n, slots[i].seed);
      break;
    }
    default:
      slots[i].seed = (unsigned)rnd();
      fill(slots[i].p, slots[i].n, slots[i].seed);
    }
  }

  for (int i = 0; i < SLOTS; i++) {
    if (slots[i].p) {
      assert(check(slots[i].p, slots[i].n, slots[i].seed));
      free(slots[i].p);
    }
  }
  assert(zones(Tiny) <= 1);
  assert(zones(Small) <= 1);
  assert(zones(Large) == large); /* every large zone was given back */
}

static void test_random_1(void) { random_run(0x9E3779B97F4A7C15ull, 20000); }
static void test_random_2(void) { random_run(0xDEADBEEFCAFEF00Dull, 20000); }
static void test_random_3(void) { random_run(42, 20000); }

static void test_alloc_free_loop(void) {
  for (int i = 0; i < 100000; i++) {
    void *p = malloc(1 + (size_t)(i * 37) % 1500);
    assert(p != NULL);
    free(p);
  }
  assert(zones(Tiny) <= 1 && zones(Small) <= 1);
}

static void many_tiny(int reverse) {
  enum { N = 10000 };
  static void *p[N];
  for (int i = 0; i < N; i++) {
    p[i] = malloc(16);
    assert(p[i] != NULL);
  }
  for (int i = 0; i < N; i++)
    free(p[reverse ? N - 1 - i : i]);
  assert(zones(Tiny) <= 1);
}
static void test_many_tiny_freed_forward(void) { many_tiny(0); }
static void test_many_tiny_freed_in_reverse(void) { many_tiny(1); }

/* Freeing every other block, then allocating again, must reuse the holes
 * instead of mapping new zones. */
static void test_fragmentation_reuses_holes(void) {
  enum { N = 1000, BLK = 64 };
  static unsigned char *p[N];
  for (int i = 0; i < N; i++) {
    p[i] = malloc(BLK);
    assert(p[i] != NULL);
    fill(p[i], BLK, (unsigned)i);
  }
  size_t before = zones(Tiny);
  for (int i = 1; i < N; i += 2)
    free(p[i]);
  for (int i = 1; i < N; i += 2) {
    p[i] = malloc(BLK);
    assert(p[i] != NULL);
    fill(p[i], BLK, (unsigned)i);
  }
  assert(zones(Tiny) == before);
  for (int i = 0; i < N; i++)
    assert(check(p[i], BLK, (unsigned)i));
}

/* Repeated fill/drain cycles must not make the heap grow. */
static void test_cycles_do_not_grow(void) {
  enum { N = 300 };
  static void *p[N];
  size_t first = 0;
  for (int cycle = 0; cycle < 20; cycle++) {
    for (int i = 0; i < N; i++) {
      p[i] = malloc(200);
      assert(p[i] != NULL);
    }
    for (int i = 0; i < N; i++)
      free(p[i]);
    size_t now = zones(Tiny) + zones(Small) + zones(Large);
    if (cycle == 0)
      first = now;
    assert(now <= first);
  }
}

static void test_mixed_classes_interleaved(void) {
  enum { N = 300 };
  static unsigned char *p[N];
  static size_t sz[N];
  for (int i = 0; i < N; i++) {
    sz[i] = (i % 3 == 0) ? 16 : (i % 3 == 1) ? 600 : 9000;
    p[i] = malloc(sz[i]);
    assert(p[i] != NULL);
    fill(p[i], sz[i], (unsigned)i);
  }
  for (int i = 0; i < N; i += 2)
    free(p[i]);
  for (int i = 1; i < N; i += 2)
    assert(check(p[i], sz[i], (unsigned)i));
  for (int i = 1; i < N; i += 2)
    free(p[i]);
}

int main(void) {
  RUN(test_random_1);
  RUN(test_random_2);
  RUN(test_random_3);
  RUN(test_alloc_free_loop);
  RUN(test_many_tiny_freed_forward);
  RUN(test_many_tiny_freed_in_reverse);
  RUN(test_fragmentation_reuses_holes);
  RUN(test_cycles_do_not_grow);
  RUN(test_mixed_classes_interleaved);
  return failures != 0;
}
