#include "color.h"
#include "y.tab.h"
#include <stdio.h>

void yyerror(const char *s) {
  fprintf(stderr, REDHB " Error: %s " CRESET "\n", s);
}

int main(void) {
  printf(".intel_syntax noprefix\n");
  printf(".text\n");
  return yyparse();
}
