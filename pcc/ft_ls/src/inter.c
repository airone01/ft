// The following is needed for getgrgid_r and getpwuid_r
// #define _POSIX_C_SOURCE 200809L

#include "ls.h"
#include <grp.h>
#include <pwd.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

#include <errno.h>

/**
 * @brief Resolves group and user names for a list of tFiles into File structs
 * @returns 0 on success
 * @returns -1 on memory allocation error
 */
int fndids(size_t nmemb, tFile efiles[], File **dfiles);

static void free_tfiles(tFile *files, size_t count) {
  if (!files)
    return;
  for (size_t i = 0; i < count; i++) {
    free(files[i].name);
    free(files[i].path);
    free(files[i].link_target);
  }
  free(files);
}

int argsi(CliOptions *opts, FileLists *flists) {
  if (!opts || !flists)
    return -1;

  flists->err_files = NULL;
  flists->nerr = 0;
  flists->files = NULL;
  flists->nfiles = 0;
  flists->dirs = NULL;
  flists->ndirs = 0;

  if (opts->npaths == 0)
    return 0;

  tFile *err_tmp = calloc(opts->npaths, sizeof(tFile));
  tFile *files_tmp = calloc(opts->npaths, sizeof(tFile));
  tFile *dirs_tmp = calloc(opts->npaths, sizeof(tFile));

  if (!err_tmp || !files_tmp || !dirs_tmp) {
    free_tfiles(err_tmp, 0);
    free_tfiles(files_tmp, 0);
    free_tfiles(dirs_tmp, 0);
    return -1;
  }

  size_t nerr = 0;
  size_t nfiles = 0;
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
      if (S_ISLNK(sb.st_mode) && !opts->longlist) {
        struct stat target_sb;
        if (stat(p, &target_sb) == 0 && S_ISDIR(target_sb.st_mode)) {
          is_dir = 1;
        }
      }

      tFile *dest;
      if (is_dir) {
        dest = &dirs_tmp[ndirs++];
      } else {
        dest = &files_tmp[nfiles++];
      }

      dest->name = strdup(p);
      dest->path = strdup(p);
      dest->stat = sb;
      dest->uid = sb.st_uid;
      dest->gid = sb.st_gid;
      dest->err_code = 0;
      if (!dest->name || !dest->path)
        goto fail;
    }
  }

  if (fndids(nerr, err_tmp, &flists->err_files) == -1)
    goto fail;
  flists->nerr = nerr;

  if (fndids(nfiles, files_tmp, &flists->files) == -1)
    goto fail;
  flists->nfiles = nfiles;

  if (fndids(ndirs, dirs_tmp, &flists->dirs) == -1)
    goto fail;
  flists->ndirs = ndirs;

  free_tfiles(err_tmp, nerr);
  free_tfiles(files_tmp, nfiles);
  free_tfiles(dirs_tmp, ndirs);
  return 0;

fail:
  free_tfiles(err_tmp, nerr);
  free_tfiles(files_tmp, nfiles);
  free_tfiles(dirs_tmp, ndirs);
  free_file_lists(flists);
  return -1;
}

int fndids(size_t nmemb, tFile efiles[], File **dfiles) {
  if (nmemb == 0) {
    *dfiles = NULL;
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
    tFile *efile = &efiles[i];
    File *file = &files[i];

    file->err_code = efile->err_code;
    if (efile->name) {
      file->name = strdup(efile->name);
      if (!file->name)
        goto fail;
    }
    if (efile->path) {
      file->path = strdup(efile->path);
      if (!file->path)
        goto fail;
    }
    file->stat = efile->stat;

    if (efile->err_code != 0) {
      continue;
    }

    struct group *grp = getgrgid(efile->stat.st_gid);
    if (grp) {
      file->group = strdup(grp->gr_name);
      if (!file->group)
        goto fail;
    } else {
      char *gn = malloc((uint64_t)grpmlen * sizeof(char));
      if (!gn)
        goto fail;
      snprintf(gn, (uint64_t)grpmlen, "%u", efile->stat.st_gid);
      file->group = gn;
    }

    struct passwd *user = getpwuid(efile->stat.st_uid);
    if (user) {
      file->user = strdup(user->pw_name);
      if (!file->user)
        goto fail;
    } else {
      char *un = malloc((uint16_t)usrmlen * sizeof(char));
      if (!un)
        goto fail;
      snprintf(un, (uint16_t)usrmlen, "%u", efile->stat.st_uid);
      file->user = un;
    }
  }

  *dfiles = files;
  return 0;

fail:
  free_files(files, nmemb);
  *dfiles = NULL;
  return -1;
}
