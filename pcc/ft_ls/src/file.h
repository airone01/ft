#ifndef FILE_H
#define FILE_H

#include "types.h"
#include <stddef.h>

/**
 * @brief Resolves group and user names for a list of TempFile into File
 * structures
 */
int resolve_owner_group(size_t nmemb, TempFile temp_files[], File **filesp);

/**
 * @brief Directory traversal cycle
 * @param dir_path Directory path to traverse
 * @param optsp Pointer to CLI options
 * @param print_header 1 to print "path:" header, 0 otherwise
 * @returns 0 on success, -1 on error
 */
int traverse_dir(const char *dir_path, const CliOptions *optsp,
                 int print_header);

/**
 * @brief Sorts an array of File structures based on options
 */
void sort_files(File *files, size_t nmemb, const CliOptions *optsp);

#endif /* FILE_H */
