#include "gen.h"

void gen_global_vec_mid(const char *lbl) {
  printf(".data\n");
  printf(".align 4\n");
  printf(".L_%s_data:\n", lbl);
}

void gen_global_vec(char *name, int size, int count) {
  int total = (size > count) ? size : count;
  if (total == 0)
    total = 1;
  int remaining = total - count;
  if (remaining > 0)
    printf("  .zero %d\n", remaining * 4);
  printf(".globl %s\n", name);
  printf("%s:\n", name);
  printf("  .long .L_%s_data\n", name);
  printf(".text\n");

  add_symbol(name, TYPE_EXTERN);
  free(name);
}

void gen_global_scal_mid(const char *lbl) {
  printf(".globl %s\n", lbl);
  printf(".data\n");
  printf(".align 4\n");
  printf("%s:\n", lbl);
}

void gen_global_scal(char *name, int count) {
  if (count == 0)
    /* Default to 0 */
    printf("  .long 0\n");
  printf(".text\n");

  add_symbol(name, TYPE_EXTERN);
  free(name);
}
