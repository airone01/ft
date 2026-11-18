#include "malloc.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

/*
 * Expected format (see malloc.h):
 *
 *   TINY : 0xA0000
 *   0xA0020 - 0xA004A : 42 bytes
 *   SMALL : 0xAD000
 *   LARGE : 0xB0000
 *   Total : 52698 bytes
 *
 * Only used blocks are listed, in increasing address order per section.
 */

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

/* ---- capture and parse the output ---- */

static char out[1 << 16];

static void capture(void) {
  fflush(stdout);
  int saved = dup(1);
  FILE *f = tmpfile();
  assert(saved >= 0 && f != NULL);
  dup2(fileno(f), 1);
  show_alloc_mem();
  fflush(stdout);
  dup2(saved, 1);
  close(saved);
  rewind(f);
  size_t n = fread(out, 1, sizeof out - 1, f);
  out[n] = '\0';
  fclose(f);
}

struct ent {
  unsigned long start, end;
  size_t bytes;
  int section; /* 0 tiny, 1 small, 2 large */
};
#define MAX_ENTS 4096
static struct ent ents[MAX_ENTS];
static size_t nents, total;
static int has_total;

static void parse(void) {
  int section = -1;
  nents = total = 0;
  has_total = 0;
  char *line = out;
  while (*line) {
    char *nl = strchr(line, '\n');
    if (nl)
      *nl = '\0';
    unsigned long a, b;
    size_t n;
    if (!strncmp(line, "TINY", 4))
      section = 0;
    else if (!strncmp(line, "SMALL", 5))
      section = 1;
    else if (!strncmp(line, "LARGE", 5))
      section = 2;
    else if (sscanf(line, " 0x%lx - 0x%lx : %zu bytes", &a, &b, &n) == 3) {
      if (nents < MAX_ENTS)
        ents[nents++] = (struct ent){a, b, n, section};
    } else if (sscanf(line, "Total : %zu bytes", &n) == 1) {
      total = n;
      has_total = 1;
    }
    if (!nl)
      break;
    line = nl + 1;
  }
}

static struct ent *find(const void *p) {
  for (size_t i = 0; i < nents; i++)
    if (ents[i].start == (unsigned long)p)
      return &ents[i];
  return NULL;
}

/* ------------------------------------------------------------------ */

static void test_prints_a_total(void) {
  capture();
  parse();
  assert(has_total);
}

static void test_sections_in_order(void) {
  assert(malloc(10) && malloc(500) && malloc(5000));
  capture();
  const char *t = strstr(out, "TINY : 0x");
  const char *s = strstr(out, "SMALL : 0x");
  const char *l = strstr(out, "LARGE : 0x");
  assert(t && s && l);
  assert(t < s && s < l);
  const char *tot = strstr(out, "Total : ");
  assert(tot && tot > l);
}

static void test_each_block_is_in_its_section(void) {
  void *a = malloc(42);
  void *b = malloc(500);
  void *c = malloc(5000);
  assert(a && b && c);
  capture();
  parse();
  struct ent *ea = find(a), *eb = find(b), *ec = find(c);
  assert(ea && eb && ec);
  assert(ea->section == 0);
  assert(eb->section == 1);
  assert(ec->section == 2);
}

/* The size shown is either the requested size or the 16-aligned one. */
static void test_reported_sizes(void) {
  size_t req[] = {1, 42, 128, 500, 1024, 5000, 100000};
  enum { N = sizeof req / sizeof *req };
  void *p[N];
  for (int i = 0; i < N; i++) {
    p[i] = malloc(req[i]);
    assert(p[i] != NULL);
  }
  capture();
  parse();
  for (int i = 0; i < N; i++) {
    struct ent *e = find(p[i]);
    assert(e != NULL);
    assert(e->end - e->start == e->bytes);
    assert(e->bytes >= req[i]);
    assert(e->bytes <= ALIGN16(req[i]));
  }
}

static void test_total_is_the_sum_of_the_lines(void) {
  for (int i = 1; i <= 50; i++)
    assert(malloc((size_t)i * 37) != NULL);
  capture();
  parse();
  assert(has_total);
  size_t sum = 0;
  for (size_t i = 0; i < nents; i++)
    sum += ents[i].bytes;
  assert(total == sum);
}

static void test_free_blocks_are_not_listed(void) {
  void *a = malloc(100);
  void *b = malloc(100);
  void *c = malloc(100);
  assert(a && b && c);
  free(b);
  capture();
  parse();
  assert(find(a) != NULL);
  assert(find(b) == NULL);
  assert(find(c) != NULL);
}

static void test_total_drops_after_free(void) {
  void *a = malloc(1000);
  assert(a != NULL);
  capture();
  parse();
  size_t before = total;
  free(a);
  capture();
  parse();
  assert(total < before);
}

static void test_sorted_within_each_section(void) {
  for (int i = 0; i < 200; i++)
    assert(malloc(1 + (size_t)(i * 13) % 900) != NULL);
  for (int i = 0; i < 5; i++)
    assert(malloc(5000 + (size_t)i * 1000) != NULL);
  capture();
  parse();
  assert(nents >= 205);
  for (size_t i = 1; i < nents; i++) {
    if (ents[i].section != ents[i - 1].section)
      continue;
    assert(ents[i].start > ents[i - 1].start);
    assert(ents[i].start >= ents[i - 1].end);
  }
}

int main(void) {
  RUN(test_prints_a_total);
  RUN(test_sections_in_order);
  RUN(test_each_block_is_in_its_section);
  RUN(test_reported_sizes);
  RUN(test_total_is_the_sum_of_the_lines);
  RUN(test_free_blocks_are_not_listed);
  RUN(test_total_drops_after_free);
  RUN(test_sorted_within_each_section);
  return failures != 0;
}
