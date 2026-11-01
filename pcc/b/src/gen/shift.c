#include "gen.h"

void gen_shift(const char *shift_instr) {
  printf("  mov ecx, eax\n");
  printf("  pop eax\n");
  printf("  %s eax, cl\n", shift_instr);
}
