/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:50:15 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:05:21 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "lexer.h" // for t_parse
# include "minishell.h"

// *************************************************************************** #
//                            Function Prototypes                              #
// *************************************************************************** #

// init_ctx.c
t_ctx		*init_ctx(int argc, char **argv, char **envp);
int			add_env_var(t_env **env_list, char *key, char *value);

// init_parse.c
t_command	*create_command(void);
t_token		*create_token(t_token_type type, char *value);
t_redir		*create_redirection(t_token_type type, char *filename);
void		init_parse_context(t_parse *parse, t_token *token);

#endif
