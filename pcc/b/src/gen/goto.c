#include "gen.h"

void gen_goto(char *lbl) {
  printf("  jmp .L_%s_%s\n", current_func_name, lbl);
  free(lbl);
}

void gen_lbl(char *lbl) {
  printf(".L_%s_%s:\n", current_func_name, lbl);
  free(lbl);
}
