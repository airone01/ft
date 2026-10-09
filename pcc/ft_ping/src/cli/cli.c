// https://man7.org/linux/man-pages/man3/getopt_long.3.html
#include <string.h>
#define _GNU_SOURCE

#include "cli.h"
#include <getopt.h>
#include <stdio.h>

static void print_help(const char *pname) {
  fprintf(stderr, "\nUsage\n");
  fprintf(stderr, "  %s [options] <destination>\n", pname);

  fprintf(stderr, "\nOptions:\n");
  fprintf(stderr, "  <destination>  FQDN or IP address\n");
  fprintf(stderr, "  -v             verbose output\n");
  fprintf(stderr, "  -?, -h, --help display a help list\n");
}

int parse_args(int argc, const char *argv[], CliOptions *optsp) {
  char c;
  static struct option long_options[] = {{"help", no_argument, 0, 'h'},
                                         {0, 0, 0, 0}};

  memset(optsp, 0, sizeof(*optsp));
  optsp->pname = argv[0];

  while ((c = (char)getopt_long(argc, (char *const *)argv, "vh?", long_options,
                                NULL)) != -1)
    switch (c) {
    case 'v':
      optsp->verbose = 1;
      break;
    case 'h':
    case '?':
      print_help(argv[0]);
      return -2;
    default:
      fprintf(stderr, "%s: invalid option -- '%c'\n", optsp->pname, c);
      print_help(argv[0]);
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
