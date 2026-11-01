#include "gen.h"

void gen_push_eax(void) { printf("  push eax\n"); }

void gen_lvalue(char *name, YYLTYPE _1) {
  /* Load left-value onto stack.
   * It needs to be in the stack because it's the most convenient way to
   * store it for easy access when handling the right-side expression. */
  Symbol *sym = get_symbol(name);
  if (sym) {
    if (sym->type == TYPE_AUTO) {
      printf("  lea eax, [ebp %d]\n", sym->offset);
    } else if (sym->type == TYPE_PARAM) {
      printf("  lea eax, [ebp + %d]\n", sym->offset);
    } else if (sym->type == TYPE_EXTERN) {
      printf("  lea eax, \"%s\"\n", sym->name);
    }
    gpe();
  } else {
    fprintf(stderr,
            "<stdin>:%d:%d: " RED "error:" CRESET " unknown variable '%s'\n",
            _1.first_line, _1.first_column, name);
  }
}
