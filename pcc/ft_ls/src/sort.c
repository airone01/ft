#include "ls.h"
#include <stdlib.h>
#include <string.h>

static _Thread_local const CliOptions *g_sort_opts = NULL;

static int file_cmp(const void *p1, const void *p2) {
  const File *f1 = (const File *)p1;
  const File *f2 = (const File *)p2;

  int cmp = 0;
  if (g_sort_opts && g_sort_opts->timesort) {
    if (f1->stat.st_mtime != f2->stat.st_mtime) {
      cmp = (f1->stat.st_mtime > f2->stat.st_mtime) ? -1 : 1;
    }
#if defined(__linux__) ||                                                      \
    (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200809L)
    else if (f1->stat.st_mtim.tv_nsec != f2->stat.st_mtim.tv_nsec) {
      cmp = (f1->stat.st_mtim.tv_nsec > f2->stat.st_mtim.tv_nsec) ? -1 : 1;
    }
#endif
  }

  if (cmp == 0) {
    cmp = strcmp(f1->name, f2->name);
  }

  if (g_sort_opts && g_sort_opts->reverse) {
    cmp = -cmp;
  }

  return cmp;
}

void sort_files(File *files, size_t count, const CliOptions *opts) {
  if (!files || count < 2)
    return;
  g_sort_opts = opts;
  qsort(files, count, sizeof(File), file_cmp);
  g_sort_opts = NULL;
}
