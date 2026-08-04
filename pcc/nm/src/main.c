#include "args.h"
#include "elf_reader.h"
#include "elf_sections.h"
#include "print.h"
#include "symbol.h"
#include "symtab.h"
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @returns -1 on failure
 * 0 on success
 */
static int process_file(const char *pname, Options opts) {
  ElfFile elf;
  if (elf_open(pname, &elf) != 0)
    return -1;

  Section symtab, strtab;
  if (elf_find_symtab(&elf, &symtab, &strtab) != 0) {
    fprintf(stderr, "%s: no symbol table found", pname);
    elf_close(&elf);
    return -1;
  }

  Symbol *syms;
  size_t nmemb;
  if (symtab_build(&elf, &symtab, &strtab, &syms, &nmemb) != 0) {
    fprintf(stderr, "%s: failed to build symbol table", pname);
    elf_close(&elf);
    return -1;
  }

  elf_close(&elf);

  syms_class(syms, nmemb);
#if FT_BONUS
  if (!opts.no_sort)
#endif
    syms_sort(syms, nmemb, opts);
  syms_print(syms, nmemb, elf.is_64bit, opts);

  syms_free(syms, nmemb);

  return 0;
}

int main(int argc, char *argv[]) {
  setlocale(LC_ALL, ""); // Needed for string comparison in print.c

  Options opts;
  int ares = argsp(argc, argv, &opts);
  if (opts.show_help)
    print_help(argv[0]);
  if (ares == 1)
    return EXIT_SUCCESS;
  if (ares == -1)
    return EXIT_FAILURE;

  if (opts.nfiles == 0) {
    static const char *default_files[] = {"a.out"};
    opts.files = default_files;
    opts.nfiles = 1;
  }

  for (size_t i = 0; i < opts.nfiles; i++) {
    if (process_file(opts.files[i], opts) != 0)
      return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
