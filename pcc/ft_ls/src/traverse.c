// https://man7.org/linux/man-pages/man2/lstat.2.html
#define _POSIX_C_SOURCE 200112L

#include "file.h"
#include "print.h"
#include "types.h"
#include "util.h"
#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

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
  TempFile *tfiles = malloc(capacity * sizeof(TempFile));
  if (!tfiles) {
    // closedir() immediately to avoid FD buildup
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
      TempFile *new_tfiles = realloc(tfiles, capacity * sizeof(TempFile));
      if (!new_tfiles) {
        free_temp_files(tfiles, nfiles);
        closedir(dp);
        return -1;
      }
      tfiles = new_tfiles;
    }

    memset(&tfiles[nfiles], 0, sizeof(TempFile));
    tfiles[nfiles].name = strdup(entry->d_name);
    tfiles[nfiles].path = path_join(dir_path, entry->d_name);
    if (!tfiles[nfiles].name || !tfiles[nfiles].path) {
      free_temp_files(tfiles, nfiles + 1);
      closedir(dp);
      return -1;
    }

    // meta enrichment
    struct stat sb;
    if (lstat(tfiles[nfiles].path, &sb) == -1) {
      tfiles[nfiles].err_code = errno;
    } else {
      tfiles[nfiles].stat = sb;
      tfiles[nfiles].uid = (int)sb.st_uid;
      tfiles[nfiles].gid = (int)sb.st_gid;
      tfiles[nfiles].err_code = 0;
      if (opts->ltype == DisplayLong) {
        tfiles[nfiles].xattr_acl = get_xattr_acl_char(tfiles[nfiles].path);
        if (S_ISLNK(sb.st_mode)) {
          tfiles[nfiles].link_target =
              read_symlink_target(tfiles[nfiles].path, sb.st_size);
        }
      }
    }
    nfiles++;
  }
  closedir(dp); // closedir() immediately to avoid FD buildup

  File *files = NULL;
  if (resolve_owner_group(nfiles, tfiles, &files) == -1) {
    free_temp_files(tfiles, nfiles);
    return -1;
  }
  free_temp_files(tfiles, nfiles);

  sort_files(files, nfiles, opts);

  print_dir_header(print_header, *opts, files, nfiles, dir_path);
  print_file_list(*opts, files, nfiles);

  // Recurse subdirectories
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
