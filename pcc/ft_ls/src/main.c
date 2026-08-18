#include "ls.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  CliOptions opts;

  int a = parseopts(argc, argv, &opts);
  if (a == -1)
    return EXIT_FAILURE;
  if (a == -2)
    return EXIT_SUCCESS;

  printf("-l: %d\n", opts.l);
}
