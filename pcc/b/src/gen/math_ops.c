#include "gen.h"

void gen_math_plus(void) {
  printf("  pop ebx\n");
  printf("  add eax, ebx\n");
}

void gen_math_minus(void) {
  printf("  pop ebx\n");
  printf("  sub ebx, eax\n");
  printf("  mov eax, ebx\n");
}

void gen_math_mult(void) {
  printf("  pop ebx\n");
  printf("  imul eax, ebx\n");
}

void gen_math_div(void) {
  printf("  mov ebx, eax\n"); // Divisor
  printf("  pop eax\n");      // Dividend
  /* "Convert Doubleword to Quadword"
   * Sign-extend `eax` into `edx`. */
  printf("  cdq\n");
  printf("  idiv ebx\n");
}

void gen_math_mod(void) {
  printf("  mov ebx, eax\n"); // Divisor
  printf("  pop eax\n");      // Dividend
  /* "Convert Doubleword to Quadword"
   * Sign-extend `eax` into `edx`. */
  printf("  cdq\n");
  printf("  idiv ebx\n");
  printf("  mov eax, edx\n"); // Remainder in edx
}
