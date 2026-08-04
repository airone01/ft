#include "symtab.h"
#include "elf_sections.h"
#include "util.h"
#include <elf.h> // glibc
#include <stdlib.h>
#include <string.h>

/**
 * @returns -1
 */
static int syms_free_names(size_t i, Symbol *syms) {
  for (size_t j = 0; j < i; j++)
    free(syms[j].name);
  free(syms);
  return -1;
}

/**
 * Symbol Resolve Name
 */
static const char *sym_res_name(const ElfFile *elf, const Section *strtab,
                                uint32_t st_name) {
  if (st_name == 0)
    // Symbol has no name. This is common for section symbols.
    return "";

  if (st_name >= strtab->size)
    // OOB malformed
    return "";

  if (strtab->offset > elf->fsize || strtab->size > elf->fsize - strtab->offset)
    // OOB unmapped mem
    return "";

  size_t maxlen = strtab->size - st_name;
  if (memchr((const char *)elf->fbase + strtab->offset + st_name, '\0',
             maxlen) == NULL) // `strtab->offset + strtab->size > elf->fsize`
    // OOB malformed
    return "";

  return (const char *)elf->fbase + strtab->offset + st_name;
}

int symtab_build(const ElfFile *elf, const Section *symtab,
                 const Section *strtab, Symbol **out, size_t *nmemb_out) {
  if (symtab->entsize == 0)
    return -1;

  size_t nmemb = symtab->size / symtab->entsize;
  Symbol *syms = calloc(nmemb, sizeof(Symbol));
  if (!syms)
    return -1;

  const unsigned char *base =
      (const unsigned char *)elf->fbase + symtab->offset;

  for (size_t i = 0; i < nmemb; i++) {
    uint32_t st_name;
    uint64_t st_value, st_size;
    uint8_t st_info;
    uint16_t st_shndx;

    if (elf->is_64bit) {
      const Elf64_Sym *sym = (const Elf64_Sym *)(base + i * symtab->entsize);
      st_name = sym->st_name;
      st_value = sym->st_value;
      st_size = sym->st_size;
      st_info = sym->st_info;
      st_shndx = sym->st_shndx;
    } else {
      const Elf32_Sym *sym = (const Elf32_Sym *)(base + i * symtab->entsize);
      st_name = sym->st_name;
      st_value = sym->st_value;
      st_size = sym->st_size;
      st_info = sym->st_info;
      st_shndx = sym->st_shndx;
    }

    const char *name = sym_res_name(elf, strtab, st_name);
    uint8_t st_type = ELF64_ST_TYPE(st_info);
    if (st_type == STT_SECTION && (name == NULL || name[0] == '\0') &&
        st_shndx != SHN_UNDEF && st_shndx != SHN_ABS &&
        st_shndx != SHN_COMMON) {
      Section sec;
      sct_fill(elf, st_shndx, &sec);
      if (sec.name)
        name = sec.name;
    }
    syms[i].name = mstrdup(name);
    if (!syms[i].name)
      return syms_free_names(i, syms);
    syms[i].value = st_value;
    syms[i].size = st_size;
    syms[i].bind = ELF64_ST_BIND(st_info); // macro is bit-identical for 32/64
    syms[i].type = st_type;
    syms[i].shndx = st_shndx;

    uint32_t sec_type = 0;
    uint64_t sec_flags = 0;
    if (st_shndx != SHN_UNDEF && st_shndx != SHN_ABS &&
        st_shndx != SHN_COMMON) {
      uint32_t s_type, s_link, s_name;
      uint64_t s_offset, s_size, s_entsize, s_flags;
      get_shdr_raw(elf, st_shndx, &s_type, &s_offset, &s_size, &s_link, &s_name,
                   &s_entsize, &s_flags);
      sec_type = s_type;
      sec_flags = s_flags;
    }

    syms[i].sec_type = sec_type;
    syms[i].sec_flags = sec_flags;
    syms[i].index = i;
  }

  *out = syms;
  *nmemb_out = nmemb;
  return 0;
}
