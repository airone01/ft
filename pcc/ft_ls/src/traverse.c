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
  size_t count = 0;
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

    if (count >= capacity) {
      capacity *= 2;
      tFile *new_tfiles = realloc(tfiles, capacity * sizeof(tFile));
      if (!new_tfiles) {
        free_tfiles(tfiles, count);
        closedir(dp);
        return -1;
      }
      tfiles = new_tfiles;
    }

    memset(&tfiles[count], 0, sizeof(tFile));
    tfiles[count].name = strdup(entry->d_name);
    tfiles[count].path = path_join(dir_path, entry->d_name);
    if (!tfiles[count].name || !tfiles[count].path) {
      free_tfiles(tfiles, count + 1);
      closedir(dp);
      return -1;
    }

    // meta enrichment
    struct stat sb;
    if (lstat(tfiles[count].path, &sb) == -1) {
      tfiles[count].err_code = errno;
    } else {
      tfiles[count].stat = sb;
      tfiles[count].uid = sb.st_uid;
      tfiles[count].gid = sb.st_gid;
      tfiles[count].err_code = 0;
    }
    count++;
  }
  closedir(dp); // closedir immediately to avoid fd buildup

  File *files = NULL;
  if (fndids(count, tfiles, &files) == -1) {
    free_tfiles(tfiles, count);
    return -1;
  }
  free_tfiles(tfiles, count);

  sort_files(files, count, opts);

  // Print header
  // TO-DO: display.c
  if (print_header) {
    printf("%s:\n", dir_path);
  }

  // Cols width
  // TO-DO: display.c
  if (opts->longlist && count > 0) {
    long long total_blocks = 0;
    for (size_t i = 0; i < count; i++) {
      if (files[i].err_code == 0) {
        total_blocks += files[i].stat.st_blocks;
      }
    }
    printf("total %lld\n", total_blocks);
  }

  // Print list
  // TO-DO: display.c
  for (size_t i = 0; i < count; i++) {
    if (files[i].err_code != 0) {
      fprintf(stderr, "ft_ls: cannot access '%s': %s\n", files[i].path,
              strerror(files[i].err_code));
    } else {
      if (opts->longlist) {
        printf("%s %s %s %s\n", files[i].name,
               files[i].user ? files[i].user : "?",
               files[i].group ? files[i].group : "?", files[i].path);
      } else {
        printf("%s\n", files[i].name);
      }
    }
  }

  // Recurse subdirs
  if (opts->recursive) {
    for (size_t i = 0; i < count; i++) {
      if (files[i].err_code == 0 && S_ISDIR(files[i].stat.st_mode)) {
        if (strcmp(files[i].name, ".") != 0 &&
            strcmp(files[i].name, "..") != 0) {
          printf("\n");
          traverse_dir(files[i].path, opts, 1);
        }
      }
    }
  }

  free_files(files, count);
  return 0;
}
