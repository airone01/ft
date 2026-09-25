// https://man7.org/linux/man-pages/man2/lstat.2.html
#define _POSIX_C_SOURCE 200112L

#include "traverse.h"
#include "../display/display.h"
#include "../format/metadata.h"
#include "../sort/sort.h"
#include "../util.h"
#include "entry.h"
#include <dirent.h>
#include <errno.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

static void meta_enrich(size_t nmemb, TempFile *temp_files,
                        const CliOptions *optsp) {
  struct stat sb;
  if (lstat(temp_files[nmemb].path, &sb) == -1) {
    temp_files[nmemb].err_code = errno;
  } else {
    temp_files[nmemb].stat = sb;
    temp_files[nmemb].uid = (int)sb.st_uid;
    temp_files[nmemb].gid = (int)sb.st_gid;
    temp_files[nmemb].err_code = 0;
    enrich_temp_file(&temp_files[nmemb], optsp);
  }
}

static void recurse_subdirs(size_t nmemb, File *files,
                            const CliOptions *optsp) {
  if (optsp->recursive) {
    for (size_t i = 0; i < nmemb; i++) {
      if (files[i].err_code == 0 && S_ISDIR(files[i].stat.st_mode)) {
        if (strcmp(files[i].name, ".") != 0 &&
            strcmp(files[i].name, "..") != 0) {
          printf("\n");
          traverse_dir(files[i].path, optsp, 1);
        }
      }
    }
  }
}

int traverse_dir(const char *dir_path, const CliOptions *optsp,
                 int print_header) {
  if (!dir_path || !optsp)
    return -1;

  DIR *dp = opendir(dir_path);
  if (!dp) {
    fprintf(stderr, "ft_ls: cannot open directory '%s': %s\n", dir_path,
            strerror(errno));
    return -1;
  }

  size_t capacity = 16;
  size_t nmemb = 0;
  TempFile *temp_files = malloc(capacity * sizeof(TempFile));
  if (!temp_files) {
    // closedir() immediately to avoid FD buildup
    closedir(dp);
    return -1;
  }

  struct dirent *entry;
  while ((entry = readdir(dp)) != NULL) {
    // Skip hidden files unless -a
    if (!optsp->all && entry->d_name[0] == '.')
      continue;

    if (nmemb >= capacity) {
      capacity *= 2;
      TempFile *new_temp_files =
          realloc(temp_files, capacity * sizeof(TempFile));
      if (!new_temp_files) {
        free_temp_files(temp_files, nmemb);
        closedir(dp);
        return -1;
      }
      temp_files = new_temp_files;
    }

    memset(&temp_files[nmemb], 0, sizeof(TempFile));
    temp_files[nmemb].name = strdup(entry->d_name);
    temp_files[nmemb].path = path_join(dir_path, entry->d_name);
    if (!temp_files[nmemb].name || !temp_files[nmemb].path) {
      free_temp_files(temp_files, nmemb + 1);
      closedir(dp);
      return -1;
    }

    meta_enrich(nmemb, temp_files, optsp);

    nmemb++;
  }
  closedir(dp); // closedir() immediately to avoid FD buildup

  File *files = NULL;
  if (resolve_owner_group(nmemb, temp_files, &files) == -1) {
    free_temp_files(temp_files, nmemb);
    return -1;
  }
  free_temp_files(temp_files, nmemb);

  sort_files(files, nmemb, optsp);

  display_list_header(print_header, *optsp, files, nmemb, dir_path);
  display_files_list(*optsp, files, nmemb);

  recurse_subdirs(nmemb, files, optsp);

  free_files(files, nmemb);
  return 0;
}
