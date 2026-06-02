
#ifndef VALIDATION_H
#define VALIDATION_H

#include "minishell.h"

// *************************************************************************** #
//                                   Macros                                    #
// *************************************************************************** #

#define MAX_INPUT_LEN 4096
#define MAX_VAR_NAME_LEN 255

// *************************************************************************** #
//                            Function Prototypes                              #
// *************************************************************************** #

// validation.c
bool validate_command(t_command *cmd, t_ctx *ctx);
bool validate_env_var_name(char *name, t_ctx *ctx);
bool validate_filename(char *filename, t_ctx *ctx);
bool validate_input_length(char *input, t_ctx *ctx);

#endif
