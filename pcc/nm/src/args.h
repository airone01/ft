#ifndef ARGS_H
#define ARGS_H

#include <stddef.h>

typedef struct {
  // Inferred options

  /** Array of pointers into argv for positional file paths */
  const char **files;
  /** Number of files */
  size_t nfiles;

  // Flags

  /** -a */
  int print_debug_syms;
  /** -g */
  int external_only;
  /** -r */
  int reverse_sort;
  /** -h */
  int show_help;
  /** -p */
  int no_sort;
  /** -t */
  int radix;
  /** -u */
  int undefined_only;
} Options;

/**
 * Parses command-line interface arguments
 *
 * @returns 0 on success (continue execution)
 * @returns 1 if help was displayed (exit success)
 * @returns -1 on error (unknown flag, invalid option)
 */
int argsp(int argc, char *argv[], Options *opts);

void print_help(char *pname);

#endif /* ARGS_H */
