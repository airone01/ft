#include "gen.h"

void gen_ival_num(int num) { printf("  .long %d\n", num); }

void gen_ival_mnum(int num) { printf("  .long -%d\n", num); }

void gen_ival_str(char *str) {
  int lbl = string_counter++;
  printf("  .section .rodata\n");
  printf("  .LC%d:\n", lbl);
  printf("    .long .LC%d+4\n", lbl);
  printf("    .string %s\n", str);
  printf("  .data\n");
  printf("  .long .LC%d\n", lbl);
  free(str);
}

void gen_ival_ident(char *str) {
  printf("  .long %s\n", str);
  free(str);
}
