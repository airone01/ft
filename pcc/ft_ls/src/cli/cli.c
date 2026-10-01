// https://man7.org/linux/man-pages/man3/getopt_long.3.html
#define _GNU_SOURCE

#include "cli.h"
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

static void print_help(const char *pname) {
  fprintf(stderr, "usage: %s [options] [file(s)...]\n", pname);
  fprintf(
      stderr,
      "List information about the FILEs (the current directory by default).\n");

  fprintf(stderr, "  -a, --all\n");
  fprintf(stderr, "         do not ignore entries starting with .\n");
  fprintf(stderr, "  -d, --directory\n");
  fprintf(stderr, "         list directories themselves, not their contents\n");
  fprintf(stderr, "  -g\n");
  fprintf(stderr, "         like -l, but do not list owner\n");
  fprintf(stderr, "  -f\n");
  fprintf(stderr, "         same as -a -U\n");
  fprintf(stderr, "  -l\n");
  fprintf(stderr, "         use a long listing format\n");
  fprintf(stderr, "  -o\n");
  fprintf(stderr, "         like -l, but do not list group information\n");
  fprintf(stderr, "  -r, --reverse\n");
  fprintf(stderr, "         reverse order while sorting\n");
  fprintf(stderr, "  -R, --recursive\n");
  fprintf(stderr, "         list subdirectories recursively\n");
  fprintf(stderr, "  -S\n");
  fprintf(stderr, "         sort by file size, largest first\n");
  fprintf(stderr, "  -t\n");
  fprintf(stderr, "         sort by time, newest first\n");
  fprintf(stderr, "  -u\n");
  fprintf(stderr, "         with -lt: sort by, and show, access time;\n");
  fprintf(stderr, "         with -l: show access time and sort by name;\n");
  fprintf(stderr, "         otherwise: sort by access time, newest first\n");
  fprintf(stderr, "  -U\n");
  fprintf(stderr, "         do not sort directory entries\n");
  fprintf(stderr, "      --zero\n");
  fprintf(stderr, "         end each output line with NUL, not newline\n");
  fprintf(stderr, "  -1\n");
  fprintf(stderr, "         list one file per line\n");
  fprintf(stderr, "      --help\n");
  fprintf(stderr, "         display this help and exit\n");
}

int parse_args(int argc, const char *argv[], CliOptions *optsp) {
  char c;
  static struct option long_options[] = {{"all", no_argument, 0, 'a'},
                                         {"directory", no_argument, 0, 'd'},
                                         {"help", no_argument, 0, 'h'},
                                         {"reverse", no_argument, 0, 'r'},
                                         {"recursive", no_argument, 0, 'R'},
                                         {"zero", no_argument, 0, 'z'},
                                         {0, 0, 0, 0}};

  optsp->display_mode = isatty(STDOUT_FILENO) ? DisplayGrid : DisplayPiped;
  optsp->sort_by = ByAlphanum;
  optsp->recursive = 0;
  optsp->all = 0;
  optsp->reverse = 0;
  optsp->directory = 0;
  optsp->use_access_time = 0;
  optsp->omit_owner_col = 0;
  optsp->omit_group_col = 0;
  optsp->eol = '\n';

  while ((c = (char)getopt_long(argc, (char *const *)argv, "1adfglorRStuU",
                                long_options, NULL)) != -1)
    switch (c) {
    case '1':
      if (optsp->display_mode != DisplayList)
        // This flag is overwritten by -l
        optsp->display_mode = DisplayPiped;
      break;
    case 'a':
      optsp->all = 1;
      break;
    case 'd':
      optsp->directory = 1;
      break;
    case 'f':
      optsp->all = 1;
      optsp->sort_by = DontSort;
      break;
    case 'g':
      optsp->omit_owner_col = 1;
      optsp->display_mode = DisplayList;
      optsp->show_date = 1;
      break;
    case 'l':
      optsp->display_mode = DisplayList;
      optsp->show_date = 1;
      break;
    case 'o':
      optsp->omit_group_col = 1;
      optsp->display_mode = DisplayList;
      optsp->show_date = 1;
      break;
    case 'r':
      optsp->reverse = 1;
      break;
    case 'R':
      optsp->recursive = 1;
      break;
    case 'S':
      optsp->sort_by = BySize;
      break;
    case 't':
      optsp->sort_by = ByTime;
      break;
    case 'u':
      optsp->use_access_time = 1;
      break;
    case 'U':
      optsp->sort_by = DontSort;
      break;
    case 'z':
      optsp->eol = '\0';
      if (optsp->display_mode != DisplayList)
        // This is overwritten by -l
        optsp->display_mode = DisplayPiped;
      break;
    default:
      fprintf(stderr, "Try '%s --help' for more information.\n", argv[0]);
      return -2;
    case 'h':
      print_help(argv[0]);
      return -2;
    }

  optsp->paths = &argv[optind];
  optsp->npaths = (size_t)(argc - optind);

  if (optsp->npaths == 0) {
    static const char *default_files[] = {"."};
    optsp->paths = default_files;
    optsp->npaths = 1;
  }

  return 0;
}
