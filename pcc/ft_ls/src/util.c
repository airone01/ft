#include "ls.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>

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

char *read_symlink_target(const char *path, off_t st_size) {
  if (!path)
    return NULL;
  size_t buflen = (st_size > 0 ? (size_t)st_size + 1 : 256);
  while (1) {
    char *buf = malloc(buflen);
    if (!buf)
      return NULL;
    ssize_t len = readlink(path, buf, buflen - 1);
    if (len == -1) {
      free(buf);
      return NULL;
    }
    if ((size_t)len < buflen - 1) {
      buf[len] = '\0';
      return buf;
    }
    free(buf);
    buflen *= 2;
  }
}

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
