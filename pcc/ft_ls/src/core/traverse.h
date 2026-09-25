#ifndef SRC_CORE_TRAVERSE_H
#define SRC_CORE_TRAVERSE_H

#include "../types.h"

/**
 * @brief Directory traversal cycle
 * @param dir_path Directory path to traverse
 * @param optsp Pointer to CLI options
 * @param print_header 1 to print "path:" header, 0 otherwise
 * @returns 0 on success, -1 on error
 */
int traverse_dir(const char *dir_path, const CliOptions *optsp,
                 int print_header);

#endif /* SRC_CORE_TRAVERSE_H */
