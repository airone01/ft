#ifndef DISPLAY_H
#define DISPLAY_H

#include "../types.h"
#include <stddef.h>
#include <sys/types.h>

/**
 * @brief Prints the directory header in list mode
 */
void display_list_header(int print_header, CliOptions opts, File *files,
                         size_t nmemb, const char *dir_path);

/**
 * @brief Displays the files in a list
 */
void display_files_list(CliOptions opts, File *files, size_t nmemb);

/**
 * @brief Displays the files in a grid
 */
void display_files_grid(CliOptions opts, File *files, size_t nmemb);

#endif /* DISPLAY_H */
