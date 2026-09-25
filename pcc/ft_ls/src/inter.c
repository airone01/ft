// The following is needed for getgrgid_r() and getpwuid_r()
#define _POSIX_C_SOURCE 200809L

#include "file.h"
#include "types.h"
#include "util.h"
#include <errno.h>
#include <grp.h>
#include <pwd.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

// Yes, this code is based on GOTO, but this was cleaner than the alternatives.
int process_cli_paths(CliOptions *opts, FileLists *flists) {
  if (!opts || !flists)
    return -1;

  flists->err_files = NULL;
  flists->nerr = 0;
  flists->files = NULL;
  flists->nmemb = 0;
  flists->dirs = NULL;
  flists->ndirs = 0;

  if (opts->npaths == 0)
    return 0;

  TempFile *err_tmp = calloc(opts->npaths, sizeof(TempFile));
  TempFile *files_tmp = calloc(opts->npaths, sizeof(TempFile));
  TempFile *dirs_tmp = calloc(opts->npaths, sizeof(TempFile));

  if (!err_tmp || !files_tmp || !dirs_tmp) {
    free_temp_files(err_tmp, 0);
    free_temp_files(files_tmp, 0);
    free_temp_files(dirs_tmp, 0);
    return -1;
  }

  size_t nerr = 0;
  size_t nmemb = 0;
  size_t ndirs = 0;

  for (size_t i = 0; i < opts->npaths; i++) {
    const char *p = opts->paths[i];
    struct stat sb;

    if (lstat(p, &sb) == -1) {
      err_tmp[nerr].name = strdup(p);
      err_tmp[nerr].path = strdup(p);
      err_tmp[nerr].err_code = errno;
      if (!err_tmp[nerr].name || !err_tmp[nerr].path)
        goto fail;
      nerr++;
    } else {
      int is_dir = S_ISDIR(sb.st_mode);
      if (S_ISLNK(sb.st_mode) && opts->ltype != DisplayLong) {
        struct stat target_sb;
        if (stat(p, &target_sb) == 0 && S_ISDIR(target_sb.st_mode)) {
          is_dir = 1;
        }
      }

      TempFile *dest;
      if (is_dir) {
        dest = &dirs_tmp[ndirs++];
      } else {
        dest = &files_tmp[nmemb++];
      }

      dest->name = strdup(p);
      dest->path = strdup(p);
      dest->stat = sb;
      dest->uid = (int)sb.st_uid;
      dest->gid = (int)sb.st_gid;
      dest->err_code = 0;
      if (opts->ltype == DisplayLong) {
        dest->xattr_acl = get_xattr_acl_char(p);
        if (S_ISLNK(sb.st_mode)) {
          dest->link_target = read_symlink_target(p, sb.st_size);
        }
      }
      if (!dest->name || !dest->path)
        goto fail;
    }
  }

  if (resolve_owner_group(nerr, err_tmp, &flists->err_files) == -1)
    goto fail;
  flists->nerr = nerr;

  if (resolve_owner_group(nmemb, files_tmp, &flists->files) == -1)
    goto fail;
  flists->nmemb = nmemb;

  if (resolve_owner_group(ndirs, dirs_tmp, &flists->dirs) == -1)
    goto fail;
  flists->ndirs = ndirs;

  free_temp_files(err_tmp, nerr);
  free_temp_files(files_tmp, nmemb);
  free_temp_files(dirs_tmp, ndirs);
  return 0;

fail:
  free_temp_files(err_tmp, nerr);
  free_temp_files(files_tmp, nmemb);
  free_temp_files(dirs_tmp, ndirs);
  free_file_lists(flists);
  return -1;
}

// Yes, GOTO
int resolve_owner_group(size_t nmemb, TempFile temp_files[], File **filesp) {
  if (nmemb == 0) {
    *filesp = NULL;
    return 0;
  }

  File *files = calloc(nmemb, sizeof(File));
  if (!files)
    return -1;

  int64_t grpmlen = sysconf(_SC_LOGIN_NAME_MAX);
  if (grpmlen == -1)
    grpmlen = 100;
  int64_t usrmlen = sysconf(_SC_GETPW_R_SIZE_MAX);
  if (usrmlen == -1)
    usrmlen = 100;

  for (size_t i = 0; i < nmemb; i++) {
    TempFile *temp_file = &temp_files[i];
    File *file = &files[i];

    file->err_code = temp_file->err_code;
    if (temp_file->name) {
      file->name = strdup(temp_file->name);
      if (!file->name)
        goto fail;
    }
    if (temp_file->path) {
      file->path = strdup(temp_file->path);
      if (!file->path)
        goto fail;
    }
    if (temp_file->link_target) {
      file->link_target = strdup(temp_file->link_target);
      if (!file->link_target)
        goto fail;
    }
    file->xattr_acl = temp_file->xattr_acl;
    file->stat = temp_file->stat;

    if (temp_file->err_code != 0) {
      continue;
    }

    struct group *grp = getgrgid(temp_file->stat.st_gid);
    if (grp) {
      file->group = strdup(grp->gr_name);
      if (!file->group)
        goto fail;
    } else {
      char *gn = malloc((uint64_t)grpmlen * sizeof(char));
      if (!gn)
        goto fail;
      snprintf(gn, (uint64_t)grpmlen, "%u", temp_file->stat.st_gid);
      file->group = gn;
    }

    struct passwd *user = getpwuid(temp_file->stat.st_uid);
    if (user) {
      file->user = strdup(user->pw_name);
      if (!file->user)
        goto fail;
    } else {
      char *un = malloc((uint16_t)usrmlen * sizeof(char));
      if (!un)
        goto fail;
      snprintf(un, (uint16_t)usrmlen, "%u", temp_file->stat.st_uid);
      file->user = un;
    }
  }

  *filesp = files;
  return 0;

fail:
  free_files(files, nmemb);
  *filesp = NULL;
  return -1;
}
