#include "args.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_help(char *pname) {
  fprintf(stderr, "usage: %s [option(s)] [--] [file(s)]\n", pname);
  fprintf(stderr, " List symbols in [file(s)] (a.out by default).\n");
  fprintf(stderr, " The options are:\n");
#if FT_BONUS
  fprintf(stderr, "  -a, --debug-syms     Display debugger-only symbols\n");
  fprintf(stderr, "  -g, --extern-only    Display only external symbols\n");
#endif
  fprintf(stderr, "  -h, --help           Display this information\n");
#if FT_BONUS
  fprintf(stderr, "  -p, --no-sort        Do not sort the symbols\n");
  fprintf(stderr, "  -r, --reverse-sort   Reverse the sense of the sort\n");
  fprintf(stderr,
          "  -t, --radix=RADIX    Use RADIX for printing symbol values\n");
  fprintf(stderr, "                       o/8 = octal, d/10 = decimal, x/16 = "
                  "hex (default)\n");
  fprintf(stderr, "  -u, --undefined-only Display only undefined symbols\n");
#endif
  fprintf(stderr, "%s: supported targets: elf64-x86-64 elf32-x86-64\n", pname);
}

#if FT_BONUS
static int radixp(const char *str, int *radix_out) {
  if (strcmp(str, "d") == 0 || strcmp(str, "10") == 0) {
    *radix_out = 10;
    return 0;
  } else if (strcmp(str, "o") == 0 || strcmp(str, "8") == 0) {
    *radix_out = 8;
    return 0;
  } else if (strcmp(str, "x") == 0 || strcmp(str, "16") == 0) {
    *radix_out = 16;
    return 0;
  }
  return -1;
}
#endif

int argsp(int argc, char *argv[], Options *opts) {
  // Temp storage pointers into argv
  opts->files = (const char **)&argv[1];
  opts->nfiles = 0;
  // Options
  opts->print_debug_syms = 0;
  opts->external_only = 0;
  opts->no_sort = 0;
  opts->reverse_sort = 0;
  opts->show_help = 0;
  opts->radix = 16;
  opts->undefined_only = 0;

  int parsing_flags = 1;

  for (int i = 1; i < argc; i++) {
    const char *arg = argv[i];

    // Positionals after `--` or non-flag argument
    if (!parsing_flags || arg[0] != '-' || arg[1] == '\0') {
      opts->files[opts->nfiles++] = arg;
      continue;
    }

    // Explicit flag terminator `--`
    if (strcmp(arg, "--") == 0) {
      parsing_flags = 0;
      continue;
    }

    // Help flag
    if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0) {
      opts->show_help = 1;
      return 1;
    }

#if FT_BONUS
    // Debug symbols flag
    if (strcmp(arg, "--debug-syms") == 0) {
      opts->print_debug_syms = 1;
      continue;
    }

    // External symbols only
    if (strcmp(arg, "--extern-only") == 0) {
      opts->external_only = 1;
      continue;
    }

    // Do not sort
    if (strcmp(arg, "--no-sort") == 0) {
      opts->no_sort = 1;
      continue;
    }

    // Reverse sort
    if (strcmp(arg, "--reverse-sort") == 0) {
      opts->reverse_sort = 1;
      continue;
    }

    // Radix
    if (strncmp(arg, "--radix=", 8) == 0) {
      const char *rx_val = arg + 8; // Pointer after '--radix='
      if (radixp(rx_val, &opts->radix) != 0) {
        fprintf(stderr, "%s: invalid radix '%s'\n", argv[0], rx_val);
        return -1;
      }
      continue;
    }

    // Undefined symbols only
    if (strcmp(arg, "--undefined-only") == 0) {
      opts->undefined_only = 1;
      continue;
    }
#endif

    // Short option parse
    if (arg[0] == '-' && arg[1] != '-') {
      for (size_t j = 1; arg[j] != '\0'; j++) {
        switch (arg[j]) {
        case 'h':
          opts->show_help = 1;
          return 1;
#if FT_BONUS
        case 'a':
          opts->print_debug_syms = 1;
          break;
        case 'g':
          opts->external_only = 1;
          break;
        case 'p':
          opts->no_sort = 1;
          break;
        case 'r':
          opts->reverse_sort = 1;
          break;
        case 't': {
          const char *val = NULL;
          if (arg[j + 1] != '\0') // Attached value
            val = &arg[j + 1];
          else if (i + 1 < argc) // Next argument value
            val = argv[++i];
          else {
            fprintf(stderr, "%s: option requires an argument -- 't'\n",
                    argv[0]);
            return -1;
          }

          if (radixp(val, &opts->radix) != 0) {
            fprintf(stderr, "%s: invalid radix '%s'\n", argv[0], val);
            return -1;
          }
          j = strlen(arg) - 1; // Advance loop to end of current argument
          break;
        }
        case 'u':
          opts->undefined_only = 1;
          break;
#endif
        default:
          fprintf(stderr, "%s: invalid option -- '%c'\n", argv[0], arg[j]);
          return -1;
        }
      }
      continue;
    }

    fprintf(stderr, "%s: unrecognized option '%s'\n", argv[0], arg);
    return -1;
  }

  return 0;
}
