
#include "fdf.h"

void args_check(int argc, char **argv) {
  (void)argv;
  if (argc != 2)
    exit_error(NULL, ERR_ARG_COUNT);
}
