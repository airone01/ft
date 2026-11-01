#include "gen.h"

void gen_break(YYLTYPE _1) {
  if (break_depth == 0) {
    fprintf(stderr,
            "<stdin>:%d:%d: " YEL "warning:" CRESET " 'break' "
            "outside of loop or switch\n",
            _1.first_line, _1.first_column);
  } else
    printf("  jmp .L%d\n", break_stack[break_depth - 1]);
}
