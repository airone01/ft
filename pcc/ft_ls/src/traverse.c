#include "ls.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

int traverse_dir(const char *dir_path, const CliOptions *opts,
                 int print_header) {
  if (!dir_path || !opts)
    return -1;

  DIR *dp = opendir(dir_path);
  if (!dp) {
    fprintf(stderr, "ft_ls: cannot open directory '%s': %s\n", dir_path,
            strerror(errno));
    return -1;
  }

  size_t capacity = 16;
  size_t nfiles = 0;
  tFile *tfiles = malloc(capacity * sizeof(tFile));
  if (!tfiles) {
    // closedir immediately to avoid fd buildup
    closedir(dp);
    return -1;
  }

  struct dirent *entry;
  while ((entry = readdir(dp)) != NULL) {
    // Skip hidden files unless -a
    if (!opts->all && entry->d_name[0] == '.')
      continue;

    if (nfiles >= capacity) {
      capacity *= 2;
      tFile *new_tfiles = realloc(tfiles, capacity * sizeof(tFile));
      if (!new_tfiles) {
        free_tfiles(tfiles, nfiles);
        closedir(dp);
        return -1;
      }
      tfiles = new_tfiles;
    }

    memset(&tfiles[nfiles], 0, sizeof(tFile));
    tfiles[nfiles].name = strdup(entry->d_name);
    tfiles[nfiles].path = path_join(dir_path, entry->d_name);
    if (!tfiles[nfiles].name || !tfiles[nfiles].path) {
      free_tfiles(tfiles, nfiles + 1);
      closedir(dp);
      return -1;
    }

    // meta enrichment
    struct stat sb;
    if (lstat(tfiles[nfiles].path, &sb) == -1) {
      tfiles[nfiles].err_code = errno;
    } else {
      tfiles[nfiles].stat = sb;
      tfiles[nfiles].uid = sb.st_uid;
      tfiles[nfiles].gid = sb.st_gid;
      tfiles[nfiles].err_code = 0;
    }
    nfiles++;
  }
  closedir(dp); // closedir immediately to avoid fd buildup

  File *files = NULL;
  if (fndids(nfiles, tfiles, &files) == -1) {
    free_tfiles(tfiles, nfiles);
    return -1;
  }
  free_tfiles(tfiles, nfiles);

  sort_files(files, nfiles, opts);

  dish(print_header, *opts, files, nfiles, dir_path);
  disl(*opts, files, nfiles);

  // Recurse subdirs
  if (opts->recursive) {
    for (size_t i = 0; i < nfiles; i++) {
      if (files[i].err_code == 0 && S_ISDIR(files[i].stat.st_mode)) {
        if (strcmp(files[i].name, ".") != 0 &&
            strcmp(files[i].name, "..") != 0) {
          printf("\n");
          traverse_dir(files[i].path, opts, 1);
        }
      }
    }
  }

  free_files(files, nfiles);
  return 0;
}
