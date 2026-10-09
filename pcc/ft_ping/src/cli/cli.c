// https://man7.org/linux/man-pages/man3/getopt_long.3.html
#define _GNU_SOURCE

#include "cli.h"
#include <errno.h>
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void print_help(FILE *stream, const char *pname) {
  fprintf(stream, "Usage: %s [OPTION...] HOST ...\n", pname);
  fprintf(stream, "Send ICMP ECHO_REQUEST packets to network hosts.\n");

  fprintf(stream, "\nOptions valid for all request types:\n");
  fprintf(stream, "  -c, --count <COUNT>  stop after sending COUNT packets\n");
  fprintf(stream, "  -v, --verbose        verbose output\n");
  fprintf(stream, "  -?, --help           display this help list\n");
}

int parse_args(int argc, const char *argv[], CliOptions *optsp) {
  char c;
  static struct option long_options[] = {{"help", no_argument, 0, '?'},
                                         {"verbose", no_argument, 0, 'v'},
                                         {0, 0, 0, 0}};

  memset(optsp, 0, sizeof(*optsp));
  optsp->pname = argv[0];
  optsp->npackets = -1;

  while ((c = (char)getopt_long(argc, (char *const *)argv, "v?c:", long_options,
                                NULL)) != -1)
    switch (c) {
    case 'c':
      char *endptr;
      errno = 0;
      long val = strtol(optarg, &endptr, 10);
      if (errno != 0 || *endptr != '\0' || val <= 0) {
        fprintf(stderr, "%s: invalid value (`%s')\n", optsp->pname, optarg);
        return -1;
      }
      optsp->npackets = val;
      break;
    case 'v':
      optsp->verbose = 1;
      break;
    case '?':
      if (optopt == 0 || optopt == '?') {
        print_help(stdout, optsp->pname);
        return -2;
      }
      fprintf(stderr, "Try '%s -?' for more information.\n", optsp->pname);
      return -2;
    default:
      fprintf(stderr, "%s: invalid option -- '%c'\n", optsp->pname, c);
      print_help(stderr, optsp->pname);
      return -1;
    }

  optsp->address = argv[optind];
  if (!optsp->address) {
    fprintf(stderr, "%s: usage error: Destination address required\n",
            optsp->pname);
    return -1;
  }

  return 0;
}
