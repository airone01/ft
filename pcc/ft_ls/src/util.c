// https://man7.org/linux/man-pages/man2/readlink.2.html
#include <sys/stat.h>
#define _POSIX_C_SOURCE 200112L

#include "types.h"
#include "util.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/xattr.h>
#include <time.h>
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
  char *d = calloc(m, sizeof(char));
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

char get_xattr_acl_char(const char *path) {
  if (!path)
    return ' ';

  ssize_t len = llistxattr(path, NULL, 0);
  if (len <= 0)
    return ' ';

  char *buf = malloc((size_t)len);
  if (!buf)
    return ' ';

  ssize_t res = llistxattr(path, buf, (size_t)len);
  if (res <= 0) {
    free(buf);
    return ' ';
  }

  int has_xattr = 0;
  int has_acl = 0;

  size_t i = 0;
  while (i < (size_t)res) {
    const char *attr = &buf[i];
    if (strcmp(attr, "system.posix_acl_access") == 0 ||
        strcmp(attr, "system.posix_acl_default") == 0) {
      has_acl = 1;
    } else {
      has_xattr = 1;
    }
    i += strlen(attr) + 1;
  }

  free(buf);

  if (has_xattr)
    return '@';
  if (has_acl)
    return '+';
  return ' ';
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

  free_files(flists->files, flists->nmemb);
  flists->files = NULL;
  flists->nmemb = 0;

  free_files(flists->dirs, flists->ndirs);
  flists->dirs = NULL;
  flists->ndirs = 0;
}

void free_temp_files(TempFile *files, size_t count) {
  if (!files)
    return;
  for (size_t i = 0; i < count; i++) {
    free(files[i].name);
    free(files[i].path);
    free(files[i].link_target);
  }
  free(files);
}

char *path_join(const char *dir, const char *file) {
  if (!dir || !file)
    return NULL;

  size_t dlen = strlen(dir);
  size_t flen = strlen(file);
  int need_slash = (dlen > 0 && dir[dlen - 1] != '/');

  size_t len = dlen + (need_slash ? 1 : 0) + flen + 1;
  char *path = malloc(len);
  if (!path)
    return NULL;

  if (need_slash)
    snprintf(path, len, "%s/%s", dir, file);
  else
    snprintf(path, len, "%s%s", dir, file);

  return path;
}

void enrich_temp_file(TempFile *tf, const CliOptions *optsp) {
  if (optsp->display_mode == DisplayLong && tf->err_code == 0) {
    tf->xattr_acl = get_xattr_acl_char(tf->path);
    if (S_ISLNK(tf->stat.st_mode)) {
      tf->link_target = read_symlink_target(tf->path, tf->stat.st_size);
    }
  }
}
