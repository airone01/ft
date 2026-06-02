
#ifndef COMMANDS_H
#define COMMANDS_H

#include "minishell.h"

// *************************************************************************** #
//                            Function Prototypes                              #
// *************************************************************************** #

// command_add.c
int command_add_redirection(t_command *cmd, t_token_type type, char *filename);

// command_new.c
t_command *command_new(void);

// command_parse.c
t_command *command_parse(t_ctx *ctx, t_token *tokens);

// command_parse_utils.c
bool handle_first_arg(t_command *cmd, char *expanded_value);
bool add_to_existing_args(t_command *cmd, char *expanded_value);
bool process_word_token(t_command *cmd, t_token *token, t_ctx *ctx);
bool process_word_token_case(t_command *cmd, t_token **current, t_ctx *ctx,
                             bool *first_arg_processed);

// command_parse_utils2.c
int handle_redirection_token(t_command *cmd, t_token *token,
                             t_token *next_token, t_ctx *ctx);
bool handle_empty_first_arg(t_command *cmd, t_token **current, t_ctx *ctx);

#endif
