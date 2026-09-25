#include "print.h"
#include "types.h"
#include <error.h>
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

void print_dir_header(int print_header, CliOptions opts, File *files,
                      size_t nmemb, const char *dir_path) {
  if (print_header)
    printf("%s:\n", dir_path);

  // Cols width
  if (opts.ltype == 2 && nmemb > 0) {
    long long total_blocks = 0;
    for (size_t i = 0; i < nmemb; i++) {
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

static ColWidth compute_col_widths(File *files, size_t nmemb) {
  ColWidth cw = {1, 1, 1, 1, 0, 0};
  for (size_t i = 0; i < nmemb; i++) {
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

static void dis_pretty(File *files, size_t nmemb) {
  if (nmemb == 0)
    return;

  struct winsize ws;
  int term_width = 80;
  if (isatty(STDOUT_FILENO) && ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == 0 &&
      ws.ws_col > 0) {
    term_width = ws.ws_col;
  }

  size_t max_len = 0;
  for (size_t i = 0; i < nmemb; i++) {
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

  int num_rows = ((int)nmemb + num_cols - 1) / num_cols;

  for (int r = 0; r < num_rows; r++) {
    for (int c = 0; c < num_cols; c++) {
      int idx = c * num_rows + r;
      if (idx < (int)nmemb) {
        if (files[idx].err_code != 0) {
          fprintf(stderr, "ft_ls: cannot access '%s': %s\n", files[idx].path,
                  strerror(files[idx].err_code));
        } else {
          int next_idx = (c + 1) * num_rows + r;
          if (c == num_cols - 1 || next_idx >= (int)nmemb) {
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

void print_file_list(CliOptions opts, File *files, size_t nmemb) {
  if (opts.ltype == DisplayPretty) {
    dis_pretty(files, nmemb);
    return;
  }

  ColWidth cw = {0, 0, 0, 0, 0, 0};
  if (opts.ltype == DisplayLong) {
    cw = compute_col_widths(files, nmemb);
  }

  for (size_t i = 0; i < nmemb; i++) {
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

void date_str(time_t mtime, char str[32]) {
  struct tm *tm_info = localtime(&mtime);
  time_t now = time(NULL);

  if (mtime > now || (now - mtime) > THRESHOLD_OLD) {
    // older file format
    strftime(str, 32, "%b %e  %Y", tm_info);
  } else {
    // recent file format
    strftime(str, 32, "%b %e %H:%M", tm_info);
  }
}

void mode_str(mode_t mode, char xattr_acl, char str[12]) {
  if (S_ISREG(mode))
    str[0] = FileRegular;
  else if (S_ISDIR(mode))
    str[0] = FileDirectory;
  else if (S_ISLNK(mode))
    str[0] = FileSymlink;
  else if (S_ISCHR(mode))
    str[0] = FileCharSpecial;
  else if (S_ISBLK(mode))
    str[0] = FileBlockSpecial;
  else if (S_ISFIFO(mode))
    str[0] = FileFifo;
  else if (S_ISSOCK(mode))
    str[0] = FileSocket;
  else
    str[0] = FileUnknown;

  str[1] = (mode & S_IRUSR) ? ModeRead : ModeOff;
  str[2] = (mode & S_IWUSR) ? ModeWrite : ModeOff;
  str[3] = (mode & S_IXUSR) ? ModeExec : ModeOff;

  str[4] = (mode & S_IRGRP) ? ModeRead : ModeOff;
  str[5] = (mode & S_IWGRP) ? ModeWrite : ModeOff;
  str[6] = (mode & S_IXGRP) ? ModeExec : ModeOff;

  str[7] = (mode & S_IROTH) ? ModeRead : ModeOff;
  str[8] = (mode & S_IWOTH) ? ModeWrite : ModeOff;
  str[9] = (mode & S_IXOTH) ? ModeExec : ModeOff;

  str[10] = (xattr_acl != '\0') ? xattr_acl : ' ';
  str[11] = '\0';
}
