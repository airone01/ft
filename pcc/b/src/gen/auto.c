#include "gen.h"

void gen_auto(const char *name) {
  add_symbol(name, TYPE_AUTO);
  printf("  push 0\n");
}

void gen_auto_list(const char *name) {
  add_symbol(name, TYPE_AUTO);
  printf("  push 0\n");
}
