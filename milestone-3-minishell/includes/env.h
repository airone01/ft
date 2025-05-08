/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:47:31 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 14:39:41 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include "minishell.h"

// *************************************************************************** #
//                            Function Prototypes                              #
// *************************************************************************** #

// env.c
char	*expand_var(t_ctx *ctx, char *var_name);
char	*append_part(char *result, char *str, int start, int end);
char	*get_env_value(t_env *env_list, char *key);
char	*get_var_name(char *str, int *pos);
char	*expand_special_var(t_ctx *ctx, char *str, int *i);

// env_utils.c
char	*expand_positional_param(char *str, int *i);
char	*expand_env_var(t_ctx *ctx, char *str, int *i);
char	*expand_variable(t_ctx *ctx, char *str, int *i);

// env_dupe.c
t_env	*duplicate_env_list(t_env *original_list);

// env_find.c
char	*env_find(t_ctx *ctx, char *var);

// env_find_bin.c
char	*env_find_bin(t_ctx *ctx, char *bin);

// env_quotes.c
char	*handle_quotes_and_vars(t_ctx *ctx, t_token *token);
char	*append_text_part(int start, int i, char *result, char *str);
char	*handle_var_expansion(t_ctx *ctx, char *str, int *i, char *result);

// env_quotes_utils.c
char	*process_string(t_ctx *ctx, char *str, char *result);

#endif
