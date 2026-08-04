#include "elf_sections.h"
#include <stdio.h>
#include <string.h>

void get_shdr_raw(const ElfFile *elf, uint16_t idx, uint32_t *type,
                  uint64_t *offset, uint64_t *size, uint32_t *link,
                  uint32_t *name_off, uint64_t *entsize, uint64_t *flags) {
  const unsigned char *shdrs = elf->shdrs;

  if (idx >= elf->shnum) {
    // OOB
    *type = 0;
    *offset = 0;
    *size = 0;
    *link = 0;
    *name_off = 0;
    *entsize = 0;
    *flags = 0;
    return;
  }

  if (elf->is_64bit) {
    const Elf64_Shdr *sh =
        (const Elf64_Shdr *)(shdrs + (size_t)idx * elf->shentsize);
    *type = sh->sh_type;
    *offset = sh->sh_offset;
    *size = sh->sh_size;
    *link = sh->sh_link;
    *name_off = sh->sh_name;
    *entsize = sh->sh_entsize;
    *flags = sh->sh_flags;
  } else {
    const Elf32_Shdr *sh =
        (const Elf32_Shdr *)(shdrs + (size_t)idx * elf->shentsize);
    *type = sh->sh_type;
    *offset = sh->sh_offset;
    *size = sh->sh_size;
    *link = sh->sh_link;
    *name_off = sh->sh_name;
    *entsize = sh->sh_entsize;
    *flags = sh->sh_flags;
  }
}

static const char *section_name(const ElfFile *elf, uint32_t name_off) {
  uint32_t type, link, dummy_name;
  uint64_t shstrtab_off, shstrtab_size, dummy_entsize, dummy_flags;
  get_shdr_raw(elf, elf->shstrndx, &type, &shstrtab_off, &shstrtab_size, &link,
               &dummy_name, &dummy_entsize, &dummy_flags);

  const char *shstrtab = (const char *)elf->fbase + shstrtab_off;
  if (name_off >= shstrtab_size)
    // OOB
    return "";
  return shstrtab + name_off;
}

static int find_section_by_name(const ElfFile *elf, const char *target,
                                uint16_t *idx_out, Section *out) {
  for (uint16_t i = 0; i < elf->shnum; i++) {
    uint32_t type, link, name_off;
    uint64_t offset, size, entsize, flags;
    get_shdr_raw(elf, i, &type, &offset, &size, &link, &name_off, &entsize,
                 &flags);

    const char *name = section_name(elf, name_off);
    if (strcmp(name, target) == 0) {
      out->name = name;
      out->offset = offset;
      out->size = size;
      out->type = type;
      out->link = link;
      out->entsize = entsize;
      out->flags = flags;
      *idx_out = i;
      return 0;
    }
  }

  return -1;
}

void sct_fill(const ElfFile *elf, uint16_t idx, Section *out) {
  uint32_t type, link, name_off;
  uint64_t offset, size, entsize, flags;
  get_shdr_raw(elf, idx, &type, &offset, &size, &link, &name_off, &entsize,
               &flags);
  out->name = section_name(elf, name_off);
  out->offset = offset;
  out->size = size;
  out->type = type;
  out->link = link;
  out->entsize = entsize;
  out->flags = flags;
}

int elf_find_symtab(const ElfFile *elf, Section *symtab_out,
                    Section *strtab_out) {
  uint16_t symtab_idx;

  if (find_section_by_name(elf, ".symtab", &symtab_idx, symtab_out) == 0) {
    sct_fill(elf, symtab_out->link, strtab_out);
    return 0;
  }

  if (find_section_by_name(elf, ".dynsym", &symtab_idx, symtab_out) == 0) {
    sct_fill(elf, symtab_out->link, strtab_out);
    return 0;
  }

  return -1;
}
