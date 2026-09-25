#include "print.h"
#include "types.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

void print_dir_header(int print_header, CliOptions opts, File *files,
                      size_t nfiles, const char *dir_path) {
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
    printf("total %lld\n", total_blocks / 2);
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

static void dis_pretty(File *files, size_t nfiles) {
  if (nfiles == 0)
    return;

  struct winsize ws;
  int term_width = 80;
  if (isatty(STDOUT_FILENO) && ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 &&
      ws.ws_col > 0) {
    term_width = ws.ws_col;
  }

  size_t max_len = 0;
  for (size_t i = 0; i < nfiles; i++) {
    if (files[i].name) {
      size_t len = strlen(files[i].name);
      if (len > max_len)
        max_len = len;
    }
  }

  int col_width = (int)max_len + 2;
  int num_cols = term_width / col_width;
  if (num_cols < 1)
    num_cols = 1;

  int num_rows = ((int)nfiles + num_cols - 1) / num_cols;

  for (int r = 0; r < num_rows; r++) {
    for (int c = 0; c < num_cols; c++) {
      int idx = c * num_rows + r;
      if (idx < (int)nfiles) {
        if (files[idx].err_code != 0) {
          fprintf(stderr, "ft_ls: cannot access '%s': %s\n", files[idx].path,
                  strerror(files[idx].err_code));
        } else {
          int next_idx = (c + 1) * num_rows + r;
          if (c == num_cols - 1 || next_idx >= (int)nfiles) {
            printf("%s", files[idx].name);
          } else {
            printf("%-*s", col_width, files[idx].name);
          }
        }
      }
    }
    printf("\n");
  }
}

void print_file_list(CliOptions opts, File *files, size_t nfiles) {
  if (opts.ltype == DisplayPretty) {
    dis_pretty(files, nfiles);
    return;
  }

  ColWidth cw = {0, 0, 0, 0, 0, 0};
  if (opts.ltype == DisplayLong) {
    cw = compute_col_widths(files, nfiles);
  }

  for (size_t i = 0; i < nfiles; i++) {
    if (files[i].err_code != 0) {
      fprintf(stderr, "ft_ls: cannot access '%s': %s\n", files[i].path,
              strerror(files[i].err_code));
    } else {
      if (opts.ltype == DisplayLong) {
        char mode_s[12];
        char date_s[32];
        mode_str(files[i].stat.st_mode, files[i].xattr_acl, mode_s);
        date_str(files[i].stat.st_mtime, date_s);
        const char *usr = files[i].user ? files[i].user : "?";
        const char *grp = files[i].group ? files[i].group : "?";

        // whether file is symlink
        if (S_ISLNK(files[i].stat.st_mode) && files[i].link_target) {
          printf("%s %*ld %-*s %-*s %*lld %s %s -> %s\n", mode_s, cw.links,
                 (long)files[i].stat.st_nlink, cw.user, usr, cw.group, grp,
                 cw.size, (long long)files[i].stat.st_size, date_s,
                 files[i].name, files[i].link_target);
        } else {
          printf("%s %*ld %-*s %-*s %*lld %s %s\n", mode_s, cw.links,
                 (long)files[i].stat.st_nlink, cw.user, usr, cw.group, grp,
                 cw.size, (long long)files[i].stat.st_size, date_s,
                 files[i].name);
        }
      } else {
        printf("%s\n", files[i].name);
      }
    }
  }
}
