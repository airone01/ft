#include "color.h"
#include "y.tab.h"
#include <stdio.h>

extern char *yytext;

void yyerror(const char *s) {
  fprintf(stderr,
          "<stdin>:%d:%d: " REDHB "fatal:" CRESET " (near '%s'): %s " CRESET
          "\n",
          yylloc.first_line, yylloc.first_column, yytext, s);
}

int main(void) {
  printf(".intel_syntax noprefix\n");
  printf(".text\n");
  return yyparse();
}
