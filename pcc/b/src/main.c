#include "c2.h"
#include "color.h"
#include "y.tab.h"
#include <stdio.h>
#include <unistd.h>

extern char *yytext;

void yyerror(const char *s) {
  fprintf(stderr, "<stdin>:%d:%d: " REDHB "fatal:" CRESET " (near '%s'): %s \n",
          yylloc.first_line, yylloc.first_column, yytext, s);
}

int main(int argc, char *argv[]) {
  (void)argc;

#ifdef FT_B_OPTI
  (void)argv;
#else
  fprintf(stderr,
          "%s: " CYN "info:" CRESET " compiler optimizations disabled\n",
          argv[0]);
#endif /* FT_B_OPTI */

#ifdef FT_B_OPTI
  FILE *tmp = tmpfile();
  if (!tmp)
    return 1;

  int saved_stdout = dup(fileno(stdout));
  dup2(fileno(tmp), fileno(stdout));
#endif /* FT_B_OPTI */

  printf(".intel_syntax noprefix\n");
  printf(".text\n");

  int ret = yyparse();

#ifdef FT_B_OPTI
  fflush(stdout);

  dup2(saved_stdout, fileno(stdout));
  close(saved_stdout);

  if (ret != 0) {
    fclose(tmp);
    return ret;
  }

  rewind(tmp);
  optimize_asm(tmp, stdout);
  fclose(tmp);
#endif /* FT_B_OPTI */

  return ret;
}
