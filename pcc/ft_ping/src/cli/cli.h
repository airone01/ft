#ifndef SRC_CLI_CLI_H
#define SRC_CLI_CLI_H

#include "../types.h"
#include <stddef.h>

/**
 * @returns 0 on success, -1 on error, -2 on success but quit immediately
 */
int parse_args(int argc, const char *argv[], CliOptions *optsp);

#endif /* SRC_CLI_CLI_H */
