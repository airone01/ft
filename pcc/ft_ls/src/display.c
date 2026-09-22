#include "ls.h"
#include <stdio.h>
#include <string.h>

void dish(int print_header, CliOptions opts, File *files, size_t nfiles,
          const char *dir_path) {
  if (print_header)
    printf("%s:\n", dir_path);

  // Cols width
  if (opts.ltype == 2 && nfiles > 0) {
    long long total_blocks = 0;
    for (size_t i = 0; i < nfiles; i++) {
      if (files[i].err_code == 0) {
        total_blocks += files[i].stat.st_blocks;
      }
    }
    printf("total %lld\n", total_blocks);
  }
}

static int get_num_digits(long long n) {
  int count = 0;
  if (n <= 0)
    count = 1;
  while (n != 0) {
    n /= 10;
    count++;
  }
  return count;
}

static ColWidth compute_col_widths(File *files, size_t nfiles) {
  ColWidth cw = {1, 1, 1, 1, 0, 0};
  for (size_t i = 0; i < nfiles; i++) {
    if (files[i].err_code != 0)
      continue;
    int link_w = get_num_digits((long)files[i].stat.st_nlink);
    if (link_w > cw.links)
      cw.links = link_w;

    const char *usr = files[i].user ? files[i].user : "?";
    int usr_w = (int)strlen(usr);
    if (usr_w > cw.user)
      cw.user = usr_w;

    const char *grp = files[i].group ? files[i].group : "?";
    int grp_w = (int)strlen(grp);
    if (grp_w > cw.group)
      cw.group = grp_w;

    int size_w = get_num_digits((long long)files[i].stat.st_size);
    if (size_w > cw.size)
      cw.size = size_w;
  }
  return cw;
}

void disl(CliOptions opts, File *files, size_t nfiles) {
  ColWidth cw = {0, 0, 0, 0, 0, 0};
  if (opts.ltype == LTypeLong) {
    cw = compute_col_widths(files, nfiles);
  }

  for (size_t i = 0; i < nfiles; i++) {
    if (files[i].err_code != 0) {
      fprintf(stderr, "ft_ls: cannot access '%s': %s\n", files[i].path,
              strerror(files[i].err_code));
    } else {
      if (opts.ltype == LTypeLong) {
        char mode_str[11];
        get_mode_string(files[i].stat.st_mode, mode_str);
        const char *usr = files[i].user ? files[i].user : "?";
        const char *grp = files[i].group ? files[i].group : "?";

        if (S_ISLNK(files[i].stat.st_mode) && files[i].link_target) {
          printf("%s %*ld %-*s %-*s %*lld %s -> %s\n", mode_str, cw.links,
                 (long)files[i].stat.st_nlink, cw.user, usr, cw.group, grp,
                 cw.size, (long long)files[i].stat.st_size, files[i].name,
                 files[i].link_target);
        } else {
          printf("%s %*ld %-*s %-*s %*lld %s\n", mode_str, cw.links,
                 (long)files[i].stat.st_nlink, cw.user, usr, cw.group, grp,
                 cw.size, (long long)files[i].stat.st_size, files[i].name);
        }
      } else if (opts.ltype == LTypePretty) {
        // basic pretty-print, TODO pad this
        printf("%s", files[i].name);
        if (i + 1 < nfiles)
          printf("  ");
      } else {
        printf("%s\n", files[i].name);
      }
    }
  }
  if (opts.ltype == LTypePretty)
    printf("\n");
}
