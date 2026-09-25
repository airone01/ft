#include "../format/metadata.h"
#include "display.h"
#include <stdio.h>
#include <string.h>

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

static void display_file(CliOptions opts, File file, ColWidth cw,
                         int any_xattr_acl) {
  if (opts.display_mode == DisplayLong) {
    char mode_s[12];
    char date_s[32];
    mode_str(file.stat.st_mode, file.xattr_acl, any_xattr_acl, mode_s);
    date_str(file.stat.st_mtime, date_s);
    const char *usr = file.user ? file.user : "?";
    const char *grp = file.group ? file.group : "?";

    // whether file is symlink
    if (S_ISLNK(file.stat.st_mode) && file.link_target) {
      printf("%s %*ld %-*s %-*s %*lld %s %s -> %s%c", mode_s, cw.links,
             (long)file.stat.st_nlink, cw.user, usr, cw.group, grp, cw.size,
             (long long)file.stat.st_size, date_s, file.name, file.link_target,
             opts.eol);
    } else {
      printf("%s %*ld %-*s %-*s %*lld %s %s%c", mode_s, cw.links,
             (long)file.stat.st_nlink, cw.user, usr, cw.group, grp, cw.size,
             (long long)file.stat.st_size, date_s, file.name, opts.eol);
    }
  } else {
    printf("%s%c", file.name, opts.eol);
  }
}

void display_files_list(CliOptions opts, File *files, size_t nmemb) {
  ColWidth cw = {0, 0, 0, 0, 0, 0};
  int any_xattr_acl = 0;
  if (opts.display_mode == DisplayLong) {
    cw = compute_col_widths(files, nmemb);
    for (size_t i = 0; i < nmemb; i++) {
      if (files[i].err_code == 0 &&
          (files[i].xattr_acl == '@' || files[i].xattr_acl == '+')) {
        any_xattr_acl = 1;
        break;
      }
    }
  }

  for (size_t i = 0; i < nmemb; i++) {
    if (files[i].err_code != 0) {
      fprintf(stderr, "ft_ls: cannot access '%s': %s%c", files[i].path,
              strerror(files[i].err_code), opts.eol);
    } else {
      display_file(opts, files[i], cw, any_xattr_acl);
    }
  }
}

void display_list_header(int print_header, CliOptions opts, File *files,
                         size_t nmemb, const char *dir_path) {
  if (print_header)
    printf("%s:%c", dir_path, opts.eol);

  // Cols width
  if (opts.display_mode == 2 && nmemb > 0) {
    long long total_blocks = 0;
    for (size_t i = 0; i < nmemb; i++) {
      if (files[i].err_code == 0) {
        total_blocks += files[i].stat.st_blocks;
      }
    }
    printf("total %lld%c", total_blocks / 2, opts.eol);
  }
}
