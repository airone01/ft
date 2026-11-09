#include "gen.h"

int is_lvalue = 0;

void gen_push_eax(void) { printf("  push eax\n"); }

void gen_lvalue_addr(char *name) {
  Symbol *sym = get_symbol(name);
  if (!sym || sym->type == TYPE_EXTERN)
    printf("  lea eax, \"%s\"\n", name);
  else if (sym->type == TYPE_AUTO)
    printf("  lea eax, [ebp %d]\n", sym->offset);
  else if (sym->type == TYPE_PARAM)
    printf("  lea eax, [ebp + %d]\n", sym->offset);
  is_lvalue = 1;
}

void ensure_rvalue(void) {
  if (is_lvalue) {
    printf("  mov eax, [eax]\n");
    is_lvalue = 0;
  }
}

void gen_assign_prep(void) {
  is_lvalue = 0;
  /* push dest addr to stack for gen_compound_ass */
  gpe();
}

void gen_unary_deref(void) {
  ensure_rvalue(); /* ensure ptr loaded in eax */
  is_lvalue = 1;
}

void gen_unary_addrof(void) {
  /* addr already in eax, now treated as rvalue */
  is_lvalue = 0;
}
