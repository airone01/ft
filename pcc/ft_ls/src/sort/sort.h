#ifndef SRC_SORT_SORT_H
#define SRC_SORT_SORT_H

#include "../types.h"
#include <stddef.h>

/**
 * @brief Sorts an array of File structures based on options
 */
void sort_files(File *files, size_t nmemb, const CliOptions *optsp);

#endif /* SRC_SORT_SORT_H */
