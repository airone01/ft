#include "display.h"
#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

void display_files_grid(CliOptions opts, File *files, size_t nmemb) {
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
          fprintf(stderr, "ft_ls: cannot access '%s': %s%c", files[idx].path,
                  strerror(files[idx].err_code), opts.eol);
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
    printf("%c", opts.eol);
  }
}
