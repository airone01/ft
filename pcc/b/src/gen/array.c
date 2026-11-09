#include "gen.h"

/*
 * Array indexing
 *
 * Separating arr_access from read vs assignment avoids the LR(1) lookahead
 * problem.
 *
 * In more detail: because we don't use an AST and have a lookahead of one
 * token, we cannot know in advance whether in `v[i]`, `i` should be treated
 * as the start of an lvalue or as an expr.
 * In a modern compiler, this problem would not arise because the first pass
 * of the compiler would resolve `v[i]` as a node of array access of `v` at
 * `i`, and later, a type-checker would run through the tree and solve the
 * sideness of `i`.
 * But, again, we don't have the luxury of an AST.
 *
 * The following is the cleanest solution I've found for this.
 * I also emulate the incrent and decrement here for better parity.
 */

void gen_arr_read(void) { printf("  mov eax, [eax]\n"); }

void gen_arr_write(void) {
  printf("  pop ebx\n");
  printf("  mov [ebx], eax\n");
}

void gen_arr_inc(void) {
  printf("  mov edx, eax\n");
  printf("  mov eax, [edx]\n");
  printf("  inc dword ptr [edx]\n");
}

void gen_arr_dec(void) {
  printf("  mov edx, eax\n");
  printf("  mov eax, [edx]\n");
  printf("  dec dword ptr [edx]\n");
}

void gen_arr_acc(void) {
  printf("  pop ebx\n");
  printf("  lea eax, [ebx + eax*4]\n");
  is_lvalue = 1;
}
