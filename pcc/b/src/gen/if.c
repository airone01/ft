#include "gen.h"

void gen_if_prec(int else_lbl) { printf(".L%d:\n", else_lbl); }

int gen_if_mid(int else_lbl) {
  int exit_lbl = label_counter++;
  printf("  jmp .L%d\n", exit_lbl); // Skip else branch
  printf(".L%d:\n", else_lbl);      // Start of else branch
  return exit_lbl;
}

void gen_if(int exit_lbl) { printf(".L%d:\n", exit_lbl); }

int gen_if_hdr(void) {
  int else_lbl = label_counter++;
  printf("  cmp eax, 0\n");
  printf("  je .L%d\n", else_lbl);
  return else_lbl;
}

int gen_ternary_mid(void) {
  int false_lbl = label_counter++;
  printf("  cmp eax, 0\n");
  printf("  je .L%d\n", false_lbl);
  return false_lbl;
}

int gen_ternary_colon(int false_lbl) {
  int exit_lbl = label_counter++;
  printf("  jmp .L%d\n", exit_lbl);
  printf(".L%d:\n", false_lbl);
  return exit_lbl;
}

void gen_ternary_end(int exit_lbl) { printf(".L%d:\n", exit_lbl); }
