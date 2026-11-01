#include "gen.h"

void gen_switch(void) {
  break_depth--;

  SwitchContext *sc = &switch_stack[switch_depth - 1];
  // Fallthrough protection for end of body
  printf("  jmp .L%d\n", sc->end_lbl);
  printf(".L%d:\n", sc->dispatch_lbl);

  // Emit comps
  for (int i = 0; i < sc->case_count; i++) {
    printf("  cmp dword ptr [esp], %d\n", sc->cases[i].val);
    printf("  je .L%d\n", sc->cases[i].lbl);
  }

  if (sc->default_lbl)
    printf("  jmp .L%d\n", sc->default_lbl);
  printf(".L%d:\n", sc->end_lbl);
  printf("  add esp, 4\n");
  pop_switch();
}

void gen_switch_start(void) {
  int dispatch_lbl = label_counter++;
  int end_lbl = label_counter++;
  break_stack[break_depth++] = end_lbl;
  push_switch(dispatch_lbl, end_lbl);
  gpe();
  printf("  jmp .L%d\n", dispatch_lbl);
}

void gen_switch_case(int num) {
  int lbl = label_counter++;
  add_case(num, lbl);
  printf(".L%d:\n", lbl);
}

void gen_switch_default(void) {
  int lbl = label_counter++;
  if (switch_depth > 0)
    switch_stack[switch_depth - 1].default_lbl = lbl;
  printf(".L%d:\n", lbl);
}
