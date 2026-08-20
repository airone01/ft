#include "ls.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static size_t nmin(size_t a, size_t b) {
  if (a < b)
    return a;
  return b;
}

char *strndup(const char *s, size_t n) {
  if (!s)
    return NULL;

  size_t m = nmin(strlen(s), n) + 1;
  char *d = malloc(m * sizeof(char));
  if (!d)
    return NULL;

  snprintf(d, m, "%s", s);
  return d;
}

char *strdup(const char *s) { return strndup(s, UINTMAX_MAX); }

void free_file(File *file) {
  if (!file)
    return;
  free(file->name);
  free(file->path);
  free(file->link_target);
  free(file->user);
  free(file->group);
}

void free_files(File *files, size_t count) {
  if (!files)
    return;
  for (size_t i = 0; i < count; i++) {
    free_file(&files[i]);
  }
  free(files);
}

void free_file_lists(FileLists *flists) {
  if (!flists)
    return;
  free_files(flists->err_files, flists->nerr);
  flists->err_files = NULL;
  flists->nerr = 0;

  free_files(flists->files, flists->nfiles);
  flists->files = NULL;
  flists->nfiles = 0;

  free_files(flists->dirs, flists->ndirs);
  flists->dirs = NULL;
  flists->ndirs = 0;
}
