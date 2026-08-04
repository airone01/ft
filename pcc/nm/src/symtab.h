#ifndef SYMTAB_H
#define SYMTAB_H

#include "elf_reader.h"
#include "elf_sections.h"
#include "symbol.h"

/**
 * Builds a Symbol[] array from the given symtab/strtab sections.
 *
 * @returns 0 on success, -1 on failure.
 * @note Caller owns *out and must call syms_free().
 */
int symtab_build(const ElfFile *elf, const Section *symtab,
                 const Section *strtab, Symbol **out, size_t *nmemb_out);

#endif /* SYMTAB_H */
