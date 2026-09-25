// https://man7.org/linux/man-pages/man2/readlink.2.html
#define _POSIX_C_SOURCE 200112L

#include "metadata.h"
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/xattr.h>

void enrich_temp_file(TempFile *tf, const CliOptions *optsp) {
  if (optsp->display_mode == DisplayLong && tf->err_code == 0) {
    tf->xattr_acl = get_xattr_acl_char(tf->path);
    if (S_ISLNK(tf->stat.st_mode)) {
      tf->link_target = read_symlink_target(tf->path, tf->stat.st_size);
    }
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
