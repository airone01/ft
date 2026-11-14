#ifndef ELF_SECTIONS_H
#define ELF_SECTIONS_H

#include "elf_reader.h"
#include <stdint.h>

typedef struct {
  const char *name;
  /**
   * sh_offset
   * @note Where the section data starts in file
   */
  uint64_t offset;
  /** sh_size */
  uint64_t size;
  /** sh_type */
  uint32_t type;
  /**
   * sh_link
   * @note Index of .symtab's strtab
   */
  uint32_t link;
  /**
   * sh_entsize
   * Size of one entry, if fixed-size
   */
  uint64_t entsize;
  /**
   * sh_flags
   * Entry flags
   */
  uint64_t flags;
} Section;

/**
 * Finds the symbol table in an ELF.
 *
 * @note This resolves the important sections up front, like symbol table & its
 * string table.
 * @note Falls back to .dysym/.dynstr if .symtab is missing (meaning it's a
 * stripped binary)
 *
 * @returns 0 on success (it found some symbol table)
 * @returns -1 if neither symbol tables exist
 */
int elf_find_symtab(const ElfFile *elf, Section *symtab_out,
                    Section *strtab_out);

/**
 * Gets raw section header
 */
void get_shdr_raw(const ElfFile *elf, uint16_t idx, uint32_t *type,
                  uint64_t *offset, uint64_t *size, uint32_t *link,
                  uint32_t *name_off, uint64_t *entsize, uint64_t *flags);

/**
 * Finds and fills a section by index
 *
 * @returns 0 on success, -1 on no symbols
 */
void sct_fill(const ElfFile *elf, uint16_t idx, Section *out);

#endif /* ELF_SECTIONS_H */
