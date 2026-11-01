#include "gen.h"

void gen_hash(void) {
  /* CVTSI2SS is hard to swallow but it converts a signed integer into a
   * scalar single-precision floating-point value (stored here into xmm0's
   * low 32 bits).
   * @see https://intel.github.io/SDM/instruction/CVTSI2SS.html */
  printf("  cvtsi2ss xmm0, eax\n");
  printf("  movd eax, xmm0\n");
}

void gen_hash_hash(void) {
  /* The inverse from above.
   * @see https://intel.github.io/SDM/instruction/CVTTSS2SI.html */
  printf("  movd xmm0, eax\n");
  printf("  cvttss2si eax, xmm0\n");
}
