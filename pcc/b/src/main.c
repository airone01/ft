// https://man7.org/linux/man-pages/man3/getopt_long.3.html
#define _GNU_SOURCE

#include "c2.h"
#include "color.h"
#include "y.tab.h"
#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char *yytext;

static void print_help(const char *pname) {
  fprintf(stderr, "usage: %s [options]\n", pname);
  fprintf(stderr, "  -h, --help\n");
  fprintf(stderr, "  -v, --version\n");
}

int parse_args(int argc, const char *argv[]) {
  char c;
  static struct option long_options[] = {{"help", no_argument, 0, 'h'},
                                         {"version", no_argument, 0, 'v'},
                                         {0, 0, 0, 0}};

  while ((c = (char)getopt_long(argc, (char *const *)argv, "hv", long_options,
                                NULL)) != -1)
    switch (c) {
    case 'h':
      print_help(argv[0]);
      return -2;
    case 'v':
      printf("bc (airone01's ft) %s\n", FT_VERSION);
      return -2;
    default:
      return 0;
    }

  return 0;
}

void yyerror(const char *s) {
  fprintf(stderr, "<stdin>:%d:%d: " REDHB "fatal:" CRESET " (near '%s'): %s \n",
          yylloc.first_line, yylloc.first_column, yytext, s);
}

int main(int argc, const char *argv[]) {
  (void)argc;

  int rparse = parse_args(argc, argv);
  if (rparse == -1)
    return EXIT_FAILURE;
  if (rparse == -2)
    return EXIT_SUCCESS;

#ifndef FT_B_OPTI
  fprintf(stderr,
          "%s: " CYN "info:" CRESET " compiler optimizations disabled\n",
          argv[0]);
#endif /* FT_B_OPTI */

#ifdef FT_B_OPTI
  FILE *tmp = tmpfile();
  if (!tmp)
    return 1;

  int saved_stdout = dup(fileno(stdout));
  dup2(fileno(tmp), fileno(stdout));
#endif /* FT_B_OPTI */

  printf(".intel_syntax noprefix\n");
  printf(".text\n");

  int ret = yyparse();

#ifdef FT_B_OPTI
  fflush(stdout);

  dup2(saved_stdout, fileno(stdout));
  close(saved_stdout);

  if (ret != 0) {
    fclose(tmp);
    return ret;
  }

  rewind(tmp);
  optimize_asm(tmp, stdout);
  fclose(tmp);
#endif /* FT_B_OPTI */

  return ret;
}
