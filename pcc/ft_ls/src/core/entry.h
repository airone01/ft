#ifndef SRC_CORE_ENTRY_H
#define SRC_CORE_ENTRY_H

#include "../types.h"
#include <stddef.h>

/**
 * @brief Options interpreter
 * Categorizes command line path arguments into three lists:
 *   1. flists->err_files: files with stat/access errors
 *   2. flists->files: non-directory files
 *   3. flists->dirs: directories
 * @returns 0 on success
 * @returns -1 on memory or system error
 */
int process_cli_paths(CliOptions *optsp, FileLists *flists);

/**
 * @brief Resolves group and user names for a list of TempFile into File
 * structures
 */
int resolve_owner_group(size_t nmemb, TempFile temp_files[], File **filesp);

#endif /* SRC_CORE_ENTRY_H */
