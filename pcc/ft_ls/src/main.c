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

  sort_files(flists.err_files, flists.nerr, &opts);
  sort_files(flists.files, flists.nfiles, &opts);
  sort_files(flists.dirs, flists.ndirs, &opts);

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

  // Dir traversal cycle
  int show_header = (flists.ndirs > 1 || flists.nfiles > 0 || flists.nerr > 0 ||
                     opts.recursive);
  for (size_t i = 0; i < flists.ndirs; i++) {
    if (i > 0 || flists.nfiles > 0) {
      printf("\n");
    }
    if (traverse_dir(flists.dirs[i].path, &opts, show_header) == -1) {
      had_error = 1;
    }
  }

  free_file_lists(&flists);

  return had_error ? EXIT_FAILURE : EXIT_SUCCESS;
}
