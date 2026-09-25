#ifndef OPTIONS_H
#define OPTIONS_H

#include "types.h"
#include <stddef.h>

/**
 * @returns 0 on success, -1 on error, -2 on success but quit immediately
 */
int parse_args(int argc, const char *argv[], CliOptions *optsp);

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

#endif /* OPTIONS_H */
