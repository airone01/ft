#include "gen.h"

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
    /* Must arrange stack again before `call`
     * So swap top of stack [esp+0] with func ptr if func had args
     * (Multiplication by 4 is for word size) */
    printf("  mov ebx, [esp+0]\n");
    printf("  mov ecx, [esp+%d]\n", argc * 4);
    printf("  mov [esp+%d], ebx\n", argc * 4);
    printf("  mov [esp+0], ecx\n");
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
   * All funcs are flobal in Blang */
  printf(".globl %s\n", fname);
  printf("%s:\n", fname);
  printf("  .long \"%s\" + 4\n", fname);
  printf("  enter 0, 0\n");
}

void gen_func_def(void) {
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
}
