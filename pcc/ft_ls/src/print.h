#ifndef DISPLAY_H
#define DISPLAY_H

#include "types.h"
#include <stddef.h>
#include <sys/types.h>
#include <time.h>

#ifndef THRESHOLD_OLD
// Threshold before file is 'old', in seconds.
#define THRESHOLD_OLD 15778463
#endif /* THRESHOLD_OLD */

/**
 * @brief Formats file time
 * @note Writes to a small string buffer `str` for simplicity
 */
void date_str(time_t mtime, char str[32]);

/**
 * @brief Formats file mode bits and xattr/acl indicator into an 11-character
 * permission string
 * @note Writes to a small string buffer `str` for simplicity
 */
void mode_str(mode_t mode, char xattr_acl, char str[12]);

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
