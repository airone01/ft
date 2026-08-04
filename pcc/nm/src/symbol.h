#ifndef SYMBOL_H
#define SYMBOL_H

#include <stddef.h>
#include <stdint.h>

typedef struct {
  char *name;
  uint64_t value;
  uint64_t size;
  /** STB_LOCAL, STB_GLOBAL, STB_WEAK */
  uint8_t bind;
  /** STT_FUNC, STT_OBJECT, ... */
  uint8_t type;
  /** section index (SHN_UNDEF = external) */
  uint16_t shndx;
  /** sh_type of the section this symbol lives in */
  uint32_t sec_type;
  /** sh_flags of that section */
  uint64_t sec_flags;
  char type_char;
  /** Original symbol table index for tie-breaking */
  size_t index;
} Symbol;

/**
 * Analyzes and classifies symbols
 */
void syms_class(Symbol *syms, size_t nmemb);

/**
 * Frees symbols
 */
void syms_free(Symbol *syms, size_t nmemb);

#endif /* SYMBOL_H */
