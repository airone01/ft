#include "gen.h"

void gen_while_mid(int start_lbl) {
  int exit_lbl = start_lbl + 1;
  printf("  cmp eax, 0\n");
  printf("  je .L%d\n", exit_lbl);
  break_stack[break_depth++] = exit_lbl;
}

void gen_while(int start_lbl) {
  int exit_lbl = start_lbl + 1;
  printf("  jmp .L%d\n", start_lbl);
  printf(".L%d:\n", exit_lbl);
  break_depth--;
}

int gen_while_start(void) {
  int start_lbl = label_counter;
  label_counter += 2;
  printf(".L%d:\n", start_lbl);
  return start_lbl;
}
