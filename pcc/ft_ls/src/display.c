#include "ls.h"
#include <stdio.h>
#include <string.h>

void dish(int print_header, CliOptions opts, File *files, size_t nfiles,
          const char *dir_path) {
  if (print_header)
    printf("%s:\n", dir_path);

  // Cols width
  if (opts.longlist && nfiles > 0) {
    long long total_blocks = 0;
    for (size_t i = 0; i < nfiles; i++) {
      if (files[i].err_code == 0) {
        total_blocks += files[i].stat.st_blocks;
      }
    }
    printf("total %lld\n", total_blocks);
  }
}

void disl(CliOptions opts, File *files, size_t nfiles) {
  for (size_t i = 0; i < nfiles; i++) {
    if (files[i].err_code != 0) {
      fprintf(stderr, "ft_ls: cannot access '%s': %s\n", files[i].path,
              strerror(files[i].err_code));
    } else {
      if (opts.longlist) {
        printf("---------- %d %s %s %s\n", 1,
               files[i].user ? files[i].user : "?",
               files[i].group ? files[i].group : "?", files[i].name);
        // missing much info
      } else {
        printf("%s\n", files[i].name);
      }
    }
  }
}
