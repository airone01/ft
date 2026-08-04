#include "elf_reader.h"
#include <elf.h> // glibc
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h> // glibc

int elf_open(const char *path, ElfFile *elf) {
  memset(elf, 0, sizeof(*elf));

  FILE *f = fopen(path, "rb");
  if (!f) {
    fprintf(stderr, "%s: open failed\n", path);
    return -1;
  }

  if (fseek(f, 0, SEEK_END) != 0) {
    fclose(f);
    return -1;
  }

  // Just checking against 32 size because it's smaller.
  // We have better checks below.
  long size = ftell(f);
  if (size < 0 || (size_t)size < sizeof(Elf32_Ehdr)) {
    fprintf(stderr, "%s: file empty or too small to be ELF\n", path);
    fclose(f);
    return -1;
  }
  size_t fsize = (size_t)size;
  int fd = fileno(f);

  // `unsigned char*` is better for arithmetic than `void*`
  unsigned char *fbase = mmap(NULL, fsize, PROT_READ, MAP_PRIVATE, fd, 0);
  fclose(f);
  if (fbase == MAP_FAILED) {
    fprintf(stderr, "%s: mmap failed\n", path);
    munmap(fbase, fsize);
    return -1;
  }

  // This is checking magic number, basically `e_ident[0..3] == "\x7fELF"`
  const unsigned char *ident = fbase;
  if (memcmp(ident, ELFMAG, SELFMAG) != 0) {
    fprintf(stderr, "%s: not an ELF file\n", path);
    munmap(fbase, fsize);
    return -1;
  }

  elf->fbase = fbase;
  elf->fsize = fsize;
  elf->is_64bit = (ident[EI_CLASS] == ELFCLASS64);
  elf->is_little_endian = (ident[EI_DATA] == ELFDATA2LSB);

  // TODO: bail on ELFCLASSNONE / ELFDATANONE / mixed-endian host because it's
  //       fucking annoying.
  //       (won't do byteswap logic and will assume little-endian for now, but
  //       should do that eventually)

  if (elf->is_64bit) {
    if (elf->fsize < sizeof(Elf64_Ehdr)) {
      fprintf(stderr, "%s: truncated ELF64 header", path);
      munmap(fbase, elf->fsize);
      return -1;
    }
    const Elf64_Ehdr *ehdr = (const Elf64_Ehdr *)(const void *)fbase;
    elf->shoff = ehdr->e_shoff;
    elf->shnum = ehdr->e_shnum;
    elf->shentsize = ehdr->e_shentsize;
    elf->shstrndx = ehdr->e_shstrndx;

    if (elf->shentsize < sizeof(Elf64_Shdr)) {
      fprintf(stderr, "%s: invalid section header size", path);
      munmap(fbase, elf->fsize);
      return -1;
    }
  } else {
    if (elf->fsize < sizeof(Elf32_Ehdr)) {
      fprintf(stderr, "%s: truncated ELF32 header", path);
      munmap(fbase, elf->fsize);
      return -1;
    }
    const Elf32_Ehdr *ehdr = (const Elf32_Ehdr *)(const void *)fbase;
    elf->shoff = ehdr->e_shoff;
    elf->shnum = ehdr->e_shnum;
    elf->shentsize = ehdr->e_shentsize;
    elf->shstrndx = ehdr->e_shstrndx;

    if (elf->shentsize < sizeof(Elf32_Shdr)) {
      fprintf(stderr, "%s: invalid section header size", path);
      munmap(fbase, elf->fsize);
      return -1;
    }
  }

  if (elf->shstrndx >= elf->shnum) {
    // OOB malformed
    fprintf(stderr, "%s: malformed ELF", path);
    munmap(fbase, elf->fsize);
    return -1;
  }

  uint64_t shtable_bytes = (uint64_t)elf->shnum * elf->shentsize;
  // Verify multiplication for overflow
  if (shtable_bytes > elf->fsize || elf->shoff > elf->fsize - shtable_bytes) {
    fprintf(stderr, "%s: section header table out of bounds", path);
    munmap(fbase, elf->fsize);
    return -1;
  }

  // Bound check section header table itself
  if (elf->shoff + shtable_bytes > elf->fsize) {
    fprintf(stderr, "%s: section header table out of bounds", path);
    munmap(fbase, elf->fsize);
    return -1;
  }

  elf->shdrs = (const unsigned char *)fbase + elf->shoff;

  return 0;
}

void elf_close(ElfFile *elf) {
  if (elf->fbase && munmap(elf->fbase, elf->fsize) == -1)
    fprintf(stderr, "munmap failed");
}
