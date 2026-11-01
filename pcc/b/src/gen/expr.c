#include "gen.h"

void gen_expr_ident(char *name) {
  /* Load value where pointed to by variable. Meaning simply loading a variable.
   */
  Symbol *sym = get_symbol(name);
  if (sym) {
    if (sym->type == TYPE_AUTO) {
      printf("  lea eax, [ebp %d]\n", sym->offset);
    } else if (sym->type == TYPE_PARAM) {
      printf("  lea eax, [ebp + %d]\n", sym->offset);
    } else if (sym->type == TYPE_EXTERN) {
      printf("  lea eax, \"%s\"\n", sym->name);
    }
    printf("  mov eax, [eax]\n");
  } else {
    fprintf(stderr, "<stdin>: " RED "error:" CRESET " unknown variable '%s'\n",
            name);
  }
}

void gen_expr_num(int num) { printf("  mov eax, %d\n", num); }

void gen_expr_addrof(void) { printf("  pop eax\n"); }

void gen_expr_deref_expr(void) { printf("  mov eax, [eax]\n"); }

void gen_expr_deref(const char *name) {
  /* Pretty cool stuff: creates an inline read-only section with the string,
   * and then load its pointer into `eax` ofc */
  printf("  .section .rodata\n");
  printf("  .LC%d:\n", string_counter);
  printf("    .long .LC%d+4\n", string_counter);
  printf("    .string %s\n", name);
  printf("  .text\n");
  printf("  mov eax, .LC%d\n", string_counter);
  string_counter++;
}

void gen_expr_ass(void) {
  /* Assignment as expression
   * (eg `var = ...` in if condition) */
  printf("  pop ebx\n");
  printf("  mov [ebx], eax\n");
}
