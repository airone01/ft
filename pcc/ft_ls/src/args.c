#define _GNU_SOURCE

#include "options.h"
#include <getopt.h>
#include <stddef.h>
#include <stdio.h>
#include <unistd.h>

void print_help(const char *pname) {
  fprintf(stderr, "usage: %s [options] [file(s)...]\n", pname);
  fprintf(
      stderr,
      "List information about the FILEs (the current directory by default).\n");

  fprintf(stderr, "  -a, --all\n");
  fprintf(stderr, "         do not ignore entries starting with .\n");
  fprintf(stderr, "  -l\n");
  fprintf(stderr, "         use a long listing format\n");
  fprintf(stderr, "  -r, --reverse\n");
  fprintf(stderr, "         reverse order while sorting\n");
  fprintf(stderr, "  -R, --recursive\n");
  fprintf(stderr, "         list subdirectories recursively\n");
  fprintf(stderr, "  -t\n");
  fprintf(stderr, "         sort by time, newest first\n");
  fprintf(stderr, "      --zero\n");
  fprintf(stderr, "         end each output line with NUL, not newline\n");
  fprintf(stderr, "  -1\n");
  fprintf(stderr, "         list one file per line\n");
  fprintf(stderr, "      --help\n");
  fprintf(stderr, "         display this help and exit\n");
}

int parse_args(int argc, const char *argv[], CliOptions *optsp) {
  char c;
  static struct option long_options[] = {
      {"help", no_argument, 0, 'h'}, {"recursive", no_argument, 0, 'R'},
      {"all", no_argument, 0, 'a'},  {"reverse", no_argument, 0, 'r'},
      {"time", no_argument, 0, 't'}, {"zero", no_argument, 0, 'z'}};

  optsp->recursive = 0;
  optsp->all = 0;
  optsp->display_mode = isatty(STDOUT_FILENO) ? DisplayPretty : DisplayPiped;
  optsp->reverse = 0;
  optsp->timesort = 0;
  optsp->eol = '\n';

  while ((c = (char)getopt_long(argc, (char *const *)argv, "1alrRt",
                                long_options, NULL)) != -1)
    switch (c) {
    case '1':
      optsp->display_mode = DisplayPiped;
      break;
    case 'a':
      optsp->all = 1;
      break;
    case 'l':
      optsp->display_mode = DisplayLong;
      optsp->showDate = 1;
      break;
    case 'r':
      optsp->reverse = 1;
      break;
    case 'R':
      optsp->recursive = 1;
      break;
    case 't':
      optsp->timesort = 1;
      break;
    case 'z':
      optsp->eol = '\0';
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
