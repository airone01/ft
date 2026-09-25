// https://man7.org/linux/man-pages/man2/readlink.2.html
#define _POSIX_C_SOURCE 200112L

#include "types.h"
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define THRESHOLD_OLD 15778463 // Threshold before file is 'old', in seconds.

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

#include <sys/xattr.h>

void mode_str(mode_t mode, char xattr_acl, char str[12]) {
  if (S_ISREG(mode))
    str[0] = '-';
  else if (S_ISDIR(mode))
    str[0] = 'd';
  else if (S_ISLNK(mode))
    str[0] = 'l';
  else if (S_ISCHR(mode))
    str[0] = 'c';
  else if (S_ISBLK(mode))
    str[0] = 'b';
  else if (S_ISFIFO(mode))
    str[0] = 'p';
  else if (S_ISSOCK(mode))
    str[0] = 's';
  else
    str[0] = '?';

  str[1] = (mode & S_IRUSR) ? 'r' : '-';
  str[2] = (mode & S_IWUSR) ? 'w' : '-';
  str[3] = (mode & S_IXUSR) ? 'x' : '-';

  str[4] = (mode & S_IRGRP) ? 'r' : '-';
  str[5] = (mode & S_IWGRP) ? 'w' : '-';
  str[6] = (mode & S_IXGRP) ? 'x' : '-';

  str[7] = (mode & S_IROTH) ? 'r' : '-';
  str[8] = (mode & S_IWOTH) ? 'w' : '-';
  str[9] = (mode & S_IXOTH) ? 'x' : '-';

  str[10] = (xattr_acl != '\0') ? xattr_acl : ' ';
  str[11] = '\0';
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

void date_str(time_t mtime, char str[32]) {
  struct tm *tm_info = localtime(&mtime);
  time_t now = time(NULL);

  if (mtime > now || (now - mtime) > THRESHOLD_OLD) {
    // older file format
    strftime(str, 32, "%b %e  %Y", tm_info);
  } else {
    // recent file format
    strftime(str, 32, "%b %e %H:%M", tm_info);
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
