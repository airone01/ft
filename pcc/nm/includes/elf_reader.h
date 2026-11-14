#define _POSIX_C_SOURCE                                                        \
  200809L // Enable POSIX functions in standard headers. Needed for fileno which
          // is needed for mmap
#ifndef ELF_READER_H
#define ELF_READER_H

#include <elf.h> // glibc
#include <stddef.h>
#include <stdint.h>

typedef struct {
  // Next two props are for mmap lifecycle

  /* File base address */
  void *fbase;
  /* File size */
  size_t fsize;

  // Next two props are for format info

  /** Whether the ELF is 64-bit */
  int is_64bit;
  /** Whether the ELF is using little-endian */
  int is_little_endian;

  // Next four props are section header info

  /** Section header table file offset */
  uint64_t shoff;
  /** Section header table entry count */
  uint16_t shnum;
  /** Section header table entry size */
  uint16_t shentsize;
  /**
   * Section header string table index
   *
   * @note Index of the section holding section "names"
   */
  uint16_t shstrndx;

  /**
   * Section headers table
   *
   * @note Convenient pointer straight to the section header array
   * @note This is still raw Elf32_Shdr* or Elf64_Shdr*, caller must know which
   */
  const void *shdrs;
} ElfFile;

int elf_open(const char *path, ElfFile *elf);
void elf_close(ElfFile *elf);

#endif /* ELF_READER_H */
