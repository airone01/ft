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

/**
 * @brief Resolves groups and users name from their ids
 * @returns 0 on success
 * @returns -1 on error
 * @returns -2 on success but quit immediately
 */
int fndids(size_t nmemb, tFile efiles[], File **dfiles);

int argsi(CliOptions *opts, File **dfiles) {
  tFile *files = malloc(opts->npaths * sizeof(tFile));
  if (!files)
    return -1;

  for (size_t i = 0; i < opts->npaths; i++) {
    struct stat sb;
    if (stat(opts->paths[i], &sb) == -1) {
      free(files);
      return -2;
    }

    files[i].stat = sb;
    files[i].path = strdup(opts->paths[i]);
    files[i].name = strdup(opts->paths[i]);
    files[i].uid = sb.st_uid;
    files[i].gid = sb.st_gid;
  }

  int r = fndids(opts->npaths, files, dfiles);
  // TO-DO: /\ error handling
  for (size_t i = 0; i < opts->npaths; i++) {
    free(files[i].path);
    free(files[i].name);
  }
  free(files);
  return r;
}

int fndids(size_t nmemb, tFile efiles[], File **dfiles) {
  File *files = calloc(nmemb, sizeof(File));
  if (!files)
    return -1;
  *dfiles = files;

  int64_t grpmlen = sysconf(_SC_LOGIN_NAME_MAX);
  if (grpmlen == -1)
    grpmlen = 100;
  int64_t usrmlen = sysconf(_SC_GETPW_R_SIZE_MAX);
  if (usrmlen == -1)
    usrmlen = 100;

  for (size_t i = 0; i < nmemb; i++) {
    tFile *efile = &efiles[i];
    File *file = &files[i];

    file->name = strdup(efile->name);
    file->path = strdup(efile->path);
    file->stat = efile->stat;

    // Note: `getgrgid_r` has better thread safety
    struct group *grp = getgrgid(efile->stat.st_gid);
    if (grp) {
      file->group = strdup(grp->gr_name);
    } else {
      char *gn = malloc((uint64_t)grpmlen * sizeof(char));
      if (gn)
        snprintf(gn, (uint64_t)grpmlen, "%u", efile->stat.st_gid);
      file->group = gn;
    }

    // Note: `getpwuid_r` has better thread safety
    struct passwd *user = getpwuid(efile->stat.st_uid);
    if (user) {
      file->user = strdup(user->pw_name);
    } else {
      char *un = malloc((uint16_t)usrmlen * sizeof(char));
      if (un)
        snprintf(un, (uint16_t)usrmlen, "%u", efile->stat.st_uid);
      file->user = un;
    }
  }
  return 0;
}
