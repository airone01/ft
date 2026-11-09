#include "gen.h"
#include <string.h>

void gen_func_call_mid(char *name) {
  /* Load function from pointer */
  Symbol *sym = get_symbol(name);
  if (!sym || sym->type == TYPE_EXTERN) {
    printf("  lea eax, \"%s\"\n", name);
  } else if (sym->type == TYPE_AUTO) {
    printf("  lea eax, [ebp %d]\n", sym->offset);
  } else if (sym->type == TYPE_PARAM) {
    printf("  lea eax, [ebp + %d]\n", sym->offset);
  }
  printf("  mov eax, [eax]\n");
  gpe();
}

void gen_func_call(int argc) {
  /* Run function from loaded pointer */
  if (argc > 0) {
    /* Reverse the stack (func_ptr + argc arguments) so that func_ptr
     * is at [esp+0] and arguments are in cdecl left-to-right order. */
    for (int i = 0; i < (argc + 1) / 2; i++) {
      int j = argc - i;
      printf("  mov ebx, [esp+%d]\n", i * 4);
      printf("  mov ecx, [esp+%d]\n", j * 4);
      printf("  mov [esp+%d], ebx\n", j * 4);
      printf("  mov [esp+%d], ecx\n", i * 4);
    }
  }
  printf("  pop eax\n");
  printf("  call eax\n");
  if (argc > 0) {
    printf("  add esp, %d\n", argc * 4);
  }
}

void gen_func_def_mid(char *fname) {
  current_func_name = fname;
  /* Function header stuff
   * All funcs are global in Blang */
  printf(".globl %s\n", fname);
  printf("%s:\n", fname);
  printf("  .long \"%s\" + 4\n", fname);
  printf("  enter 0, 0\n");
  add_symbol(fname, TYPE_EXTERN);
}

void gen_func_def(void) {
  if (current_func_name && strcmp(current_func_name, "main") == 0)
    printf("  xor eax, eax\n");
  printf("  leave\n");
  printf("  ret\n");
  /* Reset offsets for new function.
   * Needs to happen *before* params are read.
   * This is executed before every function, but at the end here because it's
   * wrapped to after the last function.
   * We cannot define it at `TOK_IDENT TOK_LPAREN` because it conflicts with
   * other parts of the parser code. */
  current_local_offset = -4;
  current_param_offset = 8;
  clear_local_symbols();
}
