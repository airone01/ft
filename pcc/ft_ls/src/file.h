#ifndef FILE_H
#define FILE_H

#include "types.h"
#include <stddef.h>

/**
 * @brief Resolves group and user names for a list of tFiles into File structs
 */
int resolve_owner_group(size_t nmemb, tFile efiles[], File **dfiles);

/**
 * @brief Directory traversal cycle
 * @param dir_path Directory path to traverse
 * @param opts CLI options
 * @param print_header 1 to print "path:" header, 0 otherwise
 * @returns 0 on success, -1 on error
 */
int traverse_dir(const char *dir_path, const CliOptions *opts,
                 int print_header);

/**
 * @brief Sorts an array of File structs based on options
 */
void sort_files(File *files, size_t count, const CliOptions *opts);

#endif /* FILE_H */
