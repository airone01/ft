
#ifndef CHECKER_H
#define CHECKER_H

#include "minishell.h"

// *************************************************************************** #
//                            Function Prototypes                              #
// *************************************************************************** #

// token_checker.c
bool validate_token_sequence(t_token *tokens);
void print_token_error(const char *s);

// token_checker_utils.c
bool check_pipe_tokens(t_token *current);
bool check_redir_combinations(t_token *current);
bool check_logical_tokens(t_token *token);

#endif
