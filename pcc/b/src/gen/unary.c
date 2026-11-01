#include "gen.h"

void gen_unary_excl(void) {
  printf("  cmp eax, 0\n");
  printf("  sete al\n");
  printf("  movzx eax, al\n");
}

void gen_unary_not(void) { printf("  not eax\n"); }

void gen_unary_neg(void) { printf("  neg eax\n"); }
