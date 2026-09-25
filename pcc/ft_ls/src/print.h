#ifndef DISPLAY_H
#define DISPLAY_H

#include "types.h"
#include <stddef.h>

typedef struct {
  int links;
  int user;
  int group;
  int size;
  int major;
  int minor;
} ColWidth;

/**
 * @brief Prints the directory header in list mode
 */
void print_dir_header(int print_header, CliOptions opts, File *files,
                      size_t nfiles, const char *dir_path);

/**
 * @brief Prints the files
 */
void print_file_list(CliOptions opts, File *files, size_t nmemb);

#endif /* DISPLAY_H */
