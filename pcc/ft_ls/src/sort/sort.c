#include "sort.h"
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static _Thread_local const CliOptions *g_sort_opts = NULL;

static int file_cmp(const void *p1, const void *p2) {
  const File *f1 = (const File *)p1;
  const File *f2 = (const File *)p2;

  int should_time_sort = 0;
  if (g_sort_opts) {
    if (g_sort_opts->timesort)
      should_time_sort = 1;
    else if (g_sort_opts->use_access_time &&
             g_sort_opts->display_mode != DisplayLong)
      should_time_sort = 1;
  }

  int cmp = 0;
  if (should_time_sort) {
    time_t t1 =
        g_sort_opts->use_access_time ? f1->stat.st_atime : f1->stat.st_mtime;
    time_t t2 =
        g_sort_opts->use_access_time ? f2->stat.st_atime : f2->stat.st_mtime;
    if (t1 != t2)
      cmp = (t1 > t2) ? -1 : 1;
#if defined(__linux__) ||                                                      \
    (defined(_POSIX_C_SOURCE) && _POSIX_C_SOURCE >= 200809L)
    // Conditional compilation my beloved <3
    else {
      long ns1 = g_sort_opts->use_access_time ? f1->stat.st_atim.tv_nsec
                                              : f1->stat.st_mtim.tv_nsec;
      long ns2 = g_sort_opts->use_access_time ? f2->stat.st_atim.tv_nsec
                                              : f2->stat.st_mtim.tv_nsec;
      if (ns1 != ns2)
        cmp = (ns1 > ns2) ? -1 : 1;
    }
#endif
  }

  if (cmp == 0) {
    cmp = strcoll(f1->name, f2->name);
  }

  if (g_sort_opts && g_sort_opts->reverse) {
    cmp = -cmp;
  }

  return cmp;
}

void sort_files(File *files, size_t nmemb, const CliOptions *optsp) {
  if (!files || nmemb < 2 || optsp->do_not_sort)
    return;
  g_sort_opts = optsp;
  qsort(files, nmemb, sizeof(File), file_cmp);
  g_sort_opts = NULL;
}
