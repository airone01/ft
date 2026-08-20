#include "ls.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, const char *argv[]) {
  CliOptions opts;
  int had_error = 0;

  int rparse = argsp(argc, argv, &opts);
  if (rparse == -1)
    return EXIT_FAILURE;
  if (rparse == -2)
    return EXIT_SUCCESS;

  FileLists flists;
  if (argsi(&opts, &flists) == -1) {
    fprintf(stderr, "%s: memory allocation failure\n", argv[0]);
    return EXIT_FAILURE;
  }

  // Errors
  if (flists.nerr > 0) {
    had_error = 1;
    for (size_t i = 0; i < flists.nerr; i++) {
      fprintf(stderr, "ft_ls: cannot access '%s': %s\n",
              flists.err_files[i].name, strerror(flists.err_files[i].err_code));
    }
  }

  // Non-dir files
  for (size_t i = 0; i < flists.nfiles; i++) {
    printf("%s\n", flists.files[i].name);
  }

  // Dirs
  for (size_t i = 0; i < flists.ndirs; i++) {
    printf("%s:\n", flists.dirs[i].name);
  }

  free_file_lists(&flists);

  return had_error ? EXIT_FAILURE : EXIT_SUCCESS;
}
