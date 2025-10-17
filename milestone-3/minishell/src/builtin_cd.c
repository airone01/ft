/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 10:01:40 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 13:58:24 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "error.h"

char	*get_target_directory(t_ctx *ctx, t_command *cmd)
{
	char	*target_dir;

	if (cmd->arg_count == 0 || ft_strncmp(cmd->args[1], "~", 2) == 0)
		target_dir = get_home_dir(ctx);
	else if (ft_strncmp(cmd->args[1], "-", 2) == 0)
		target_dir = get_old_pwd(ctx);
	else if (ft_strncmp(cmd->args[1], ".", 2) == 0)
		target_dir = handle_dot_directory();
	else
		target_dir = ft_strdup(cmd->args[1]);
	return (target_dir);
}

/**
 * @brief Gets the current PWD directory from environment
 *
 * @return char* Current PWD or NULL if not found
 */
static char	*get_current_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
		return (pwd);
	return (ft_strdup(""));
}

/**
 * @brief Updates PWD and OLDPWD environment variables
 *
 * @param ctx Context for shell environment
 * @param old_pwd Old PWD value
 */
static void	update_environment_vars(t_ctx *ctx, char *old_pwd)
{
	t_env	*old_pwd_node;
	char	*new_pwd;

	new_pwd = getcwd(NULL, 0);
	if (!new_pwd)
	{
		free(old_pwd);
		return ;
	}
	old_pwd_node = update_pwd_variable(ctx->env_list, new_pwd);
	update_oldpwd_variable(old_pwd_node, old_pwd);
}

/**
 * @brief Executes the cd built-in command
 *
 * @param ctx Context for shell environment
 * @param cmd Command containing arguments
 * @return int Exit status (0 for success, non-zero for error)
 */
int	builtin_cd(t_ctx *ctx, t_command *cmd)
{
	char	*target_dir;
	char	*old_pwd;
	int		result;

	if (cmd->arg_count > 1)
		return (error(NULL, "cd", ERR_TOO_MANY_ARGS), 1);
	old_pwd = get_current_pwd();
	target_dir = get_target_directory(ctx, cmd);
	if (!target_dir)
		return (free(old_pwd), 1);
	result = chdir(target_dir);
	if (result != 0)
	{
		error(target_dir, "cd", ERR_NO_FILE);
		free(target_dir);
		free(old_pwd);
		return (1);
	}
	update_environment_vars(ctx, old_pwd);
	free(target_dir);
	return (0);
}
