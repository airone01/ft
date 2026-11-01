#include "gen.h"

void gen_math_fplus(void) {
  printf("  pop ebx\n");
  printf("  movd xmm1, ebx\n");
  printf("  movd xmm0, eax\n");
  printf("  addss xmm1, xmm0\n");
  printf("  movd eax, xmm1\n");
}

void gen_math_fminus(void) {
  printf("  pop ebx\n");
  printf("  movd xmm1, ebx\n");
  printf("  movd xmm0, eax\n");
  printf("  subss xmm1, xmm0\n");
  printf("  movd eax, xmm1\n");
}

void gen_math_fmult(void) {
  printf("  pop ebx\n");
  printf("  movd xmm1, ebx\n");
  printf("  movd xmm0, eax\n");
  printf("  mulss xmm1, xmm0\n");
  printf("  movd eax, xmm1\n");
}

void gen_math_fdiv(void) {
  printf("  pop ebx\n");
  printf("  movd xmm1, ebx\n");
  printf("  movd xmm0, eax\n");
  printf("  divss xmm1, xmm0\n");
  printf("  movd eax, xmm1\n");
}

void gen_math_fmod(void) {}
