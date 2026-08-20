#define _GNU_SOURCE

#include "ls.h"
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
  fprintf(stderr, "      --help\n");
  fprintf(stderr, "         display this help and exit\n");
}

int argsp(int argc, const char *argv[], CliOptions *opts) {
  char c;
  static struct option long_options[] = {
      {"help", no_argument, 0, 'h'}, {"recursive", no_argument, 0, 'R'},
      {"all", no_argument, 0, 'a'},  {"reverse", no_argument, 0, 'r'},
      {"time", no_argument, 0, 't'},
  };

  opts->recursive = 0;
  opts->all = 0;
  opts->longlist = 0;
  opts->reverse = 0;
  opts->timesort = 0;

  while ((c = (char)getopt_long(argc, (char *const *)argv, "alrRt",
                                long_options, NULL)) != -1)
    switch (c) {
    case 'a':
      opts->all = 1;
      break;
    case 'l':
      opts->longlist = 1;
      break;
    case 'r':
      opts->reverse = 1;
      break;
    case 'R':
      opts->recursive = 1;
      break;
    case 't':
      opts->timesort = 1;
      break;
    default:
      fprintf(stderr, "Try '%s --help' for more information.\n", argv[0]);
      return -2;
    case 'h':
      print_help(argv[0]);
      return -2;
    }

  opts->paths = &argv[optind];
  opts->npaths = (size_t)(argc - optind);

  if (opts->npaths == 0) {
    static const char *default_files[] = {"."};
    opts->paths = default_files;
    opts->npaths = 1;
  }

  return 0;
}
