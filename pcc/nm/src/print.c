#include "print.h"
#include "args.h"
#include "symbol.h"
#include <elf.h> // glibc
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int comp_sym_alph(const void *a, const void *b) {
  const Symbol *syma = (const Symbol *)a;
  const Symbol *symb = (const Symbol *)b;

  // System locale collation
  int res = strcoll(syma->name, symb->name);
  if (res != 0)
    return res;

  // Original symbol table index
  if (syma->index < symb->index)
    return -1;
  if (syma->index > symb->index)
    return 1;
  return 0;
}

void syms_print(const Symbol *syms, size_t nmemb, int is_64bit, Options opts) {
  int width = is_64bit ? 16 : 8;
  const char *fmt_addr = "%0*lx %c %s\n";

  // Field width should be kept fixed at 16 chars for 64bit and 8 for 32bit bins
  // regardless of radix.
  if (opts.radix == 10) {
    fmt_addr = "%0*lu %c %s\n";
  } else if (opts.radix == 8) {
    fmt_addr = "%0*lo %c %s\n";
  }

  for (size_t i = 0; i < nmemb; i++) {
    if (syms[i].name == NULL || syms[i].name[0] == '\0')
      continue;

    if (opts.undefined_only && syms[i].shndx != SHN_UNDEF)
      continue;

    if (opts.external_only && syms[i].bind == STB_LOCAL)
      continue;

    if (!opts.print_debug_syms) {
      if (syms[i].type == STT_FILE || syms[i].type_char == 'a' ||
          syms[i].type == STT_SECTION)
        continue;
    }

    if (syms[i].shndx == SHN_UNDEF) {
      printf("%*s %c %s\n", width, "", syms[i].type_char, syms[i].name);
    } else {
      printf(fmt_addr, width, (unsigned long)syms[i].value, syms[i].type_char,
             syms[i].name);
    }
  }
}

void syms_sort(Symbol *syms, size_t nmemb, Options opts) {
  (void)opts;
#if FT_BONUS
  if (opts.no_sort)
    return;
#endif

  qsort(syms, nmemb, sizeof(Symbol), comp_sym_alph);

#if FT_BONUS
  if (opts.reverse_sort) {
    for (size_t i = 0; i < nmemb / 2; i++) {
      Symbol tmp = syms[i];
      syms[i] = syms[nmemb - 1 - i];
      syms[nmemb - 1 - i] = tmp;
    }
  }
#endif
}
