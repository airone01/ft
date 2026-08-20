#include "ls.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[]) {
  CliOptions opts;
  int had_error = 0;

  int rparse = argsp(argc, argv, &opts);
  if (rparse == -1)
    return EXIT_FAILURE;
  if (rparse == -2)
    return EXIT_SUCCESS;

  File *files = NULL;

  int rinter = argsi(&opts, &files);
  if (rinter == -1)
    had_error = 1;

  if (files) {
    for (size_t i = 0; i < opts.npaths; i++)
      printf("%s\n", files[i].group);

    free_files(files, opts.npaths);
  }

  return had_error ? EXIT_FAILURE : EXIT_SUCCESS;
}
