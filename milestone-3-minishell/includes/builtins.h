/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:51:56 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:00:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

// *************************************************************************** #
//                            Function Prototypes                              #
// *************************************************************************** #

// builtin_cd.c
char	*get_target_directory(t_ctx *ctx, t_command *cmd);
int		builtin_cd(t_ctx *ctx, t_command *cmd);

// builtin_cd_utils.c
char	*get_old_pwd(t_ctx *ctx);
char	*get_home_dir(t_ctx *ctx);
t_env	*update_pwd_variable(t_env *env_node, char *new_pwd);
void	update_oldpwd_variable(t_env *old_pwd_node, char *old_pwd);
char	*handle_dot_directory(void);

// builtin_echo.c
int		builtin_echo(t_ctx *ctx, t_command *cmd);

// builtin_env.c
int		builtin_env(t_ctx *ctx, t_command *cmd);

// builtin_exit.c
int		builtin_exit(t_ctx *ctx, t_command *cmd);

// builtin_export.c
bool	validate_env_key(char *key);
char	*get_env_value_from_export(char *arg);
int		builtin_export(t_ctx *ctx, t_command *cmd);

// builtin_export_utils.c
bool	is_valid_env_char(char c);
char	*get_env_key_from_export(char *arg);
void	print_export_env(t_ctx *ctx);
bool	update_env_var(t_env **env_list, char *key, char *value,
			bool has_equals);

// builtin_export_utils2.c
int		extract_export_data(char *arg, char **key_ptr, char **value_ptr,
			bool *has_equals_ptr);
int		update_or_add_env_var(t_ctx *ctx, char *key, char *value,
			bool has_equals);

// builtin_pwd.c
int		builtin_pwd(void);

// builtin_unset.c
bool	remove_env_var(t_env **env_list, char *key);
int		builtin_unset(t_ctx *ctx, t_command *cmd);

#endif
