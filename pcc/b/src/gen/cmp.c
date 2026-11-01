#include "gen.h"

void gen_cmp(const char *set_instr) {
  printf("  pop ebx\n");
  printf("  cmp ebx, eax\n");
  printf("  %s al\n", set_instr);
  // `movzx eax, al` left-appends zeroes to `al`
  printf("  movzx eax, al\n");
}

void gen_bit_cmp(const char *set_instr) {
  printf("  pop ebx\n");
  printf("  %s eax, ebx\n", set_instr);
}

void gen_fcmp(const char *set_instr) {
  printf("  pop ebx\n");
  printf("  movd xmm1, ebx\n");
  printf("  movd xmm0, eax\n");
  /* Unordered Compare Scalar Single-precision floating-point values
   * https://intel.github.io/SDM/instruction/UCOMISS.html */
  printf("  ucomiss xmm1, xmm0\n");
  printf("  %s al\n", set_instr);
  // `movzx eax, al` left-appends zeroes to `al`
  printf("  movzx eax, al\n");
}
