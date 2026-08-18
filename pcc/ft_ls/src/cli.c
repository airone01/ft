#define _GNU_SOURCE 1

#include "ls.h"
#include <getopt.h>
#include <stdio.h>
#include <unistd.h>

void print_help(char *progname) {
  fprintf(stderr, "usage: %s [options] [file(s)...]\n", progname);
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

/**
 * @returns 0 on success
 * @returns -1 on error
 * @returns -2 on success but quit
 */
int parseopts(int argc, char *argv[], CliOptions *opts) {
  char c;
  static struct option long_options[] = {
      {"help", no_argument, 0, 'h'}, {"recursive", no_argument, 0, 'R'},
      {"all", no_argument, 0, 'a'},  {"reverse", no_argument, 0, 'r'},
      {"time", no_argument, 0, 't'},
  };

  while ((c = (char)getopt_long(argc, argv, "alrRt", long_options, NULL)) != -1)
    switch (c) {
    case 'a':
      opts->a = 1;
      break;
    case 'h':
      print_help(argv[0]);
      return -2;
    case 'l':
      opts->l = 1;
      break;
    case 'r':
      opts->r = 1;
      break;
    case 'R':
      opts->R = 1;
      break;
    case 't':
      opts->t = 1;
      break;
    }

  return 0;
}
