#include "symbol.h"
#include <ctype.h>
#include <elf.h> // glibc
#include <stdlib.h>
#include <string.h>

static void sym_classify(Symbol *sym) {
  char c = '?';

  // Special section indexes first
  if (sym->shndx == SHN_UNDEF) {
    c = 'U';
  } else if (sym->shndx == SHN_ABS) {
    c = 'A';
  } else if (sym->shndx == SHN_COMMON) {
    c = 'C';
  }
  // Special symbol types
  else if (sym->type == STT_FILE) {
    c = 'a';
  }
  // Section flags and types
  else if (sym->sec_type == SHT_NOBITS) {
    // BSS
    c = 'B';
  } else if (sym->sec_flags & SHF_EXECINSTR) {
    // Text
    c = 'T';
  } else if (sym->sec_flags & SHF_ALLOC) {
    if (sym->sec_flags & SHF_WRITE)
      // Data (R/W)
      c = 'D';
    else
      // Data (R)
      c = 'R';
  } else {
    // Debug or non-allocated
    c = 'N';
  }

  // Binding
  if (sym->bind == STB_GNU_UNIQUE) {
    c = 'u';
  } else if (sym->bind == STB_WEAK) {
    if (sym->type == STT_OBJECT)
      c = (sym->shndx == SHN_UNDEF) ? 'v' : 'V';
    else
      c = (sym->shndx == SHN_UNDEF) ? 'w' : 'W';
  } else if (sym->bind == STB_LOCAL) {
    if (c != 'N' ||
        // Need strncmp() and not strcmp() because ".debug" could be longer i.e.
        // ".debug_whatever"
        (sym->type == STT_SECTION && strncmp(sym->name, ".debug", 6) != 0))
      c = (char)tolower((unsigned char)c);
  }

  sym->type_char = c;
}

void syms_class(Symbol *syms, size_t nmemb) {
  for (size_t i = 0; i < nmemb; i++)
    sym_classify(&syms[i]);
}

void syms_free(Symbol *syms, size_t nmemb) {
  for (size_t i = 0; i < nmemb; i++)
    free(syms[i].name);
  free(syms);
}
