#include "asm.h"
#include <stdio.h>

void gen_push_eax(void) { printf("  push eax\n"); }

void gen_cmp(const char *set_instr) {
  printf("  pop ebx\n");
  printf("  cmp ebx, eax\n");
  printf("  %s al\n", set_instr);
  printf("  movzx eax, al\n");
}

void gen_bit_cmp(const char *set_instr) {
  printf("  pop ebx\n");
  printf("  %s eax, ebx\n", set_instr);
}

void gen_shift(const char *shift_instr) {
  printf("  mov ecx, eax\n");
  printf("  pop eax\n");
  printf("  %s eax, cl\n", shift_instr);
}
