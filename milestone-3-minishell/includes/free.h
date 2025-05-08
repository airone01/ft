/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:49:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 14:04:32 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FREE_H
# define FREE_H

# include "minishell.h"

// *************************************************************************** #
//                            Function Prototypes                              #
// *************************************************************************** #

// free_2d_array.c
void	free_2d_array(void **ptrs);

// free_ctx.c
void	ctx_clear(t_ctx *ctx);

// free_env.c
void	free_env_list(t_env *env_list);
int		parse_env_var(char *env_str, t_env **env_list);

// free_command.c
void	free_command(t_command *cmd);
void	free_all_commands(t_command *cmd);

#endif
