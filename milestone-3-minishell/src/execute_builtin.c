/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:45:23 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:08:24 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "execute.h"

/**
 * @brief Executes a built-in command
 *
 * Applies redirections, executes the builtin, and restores file descriptors
 *
 * @param ctx Shell context
 * @param cmd Command to execute
 * @return int Exit status
 */
int	execute_builtin(t_ctx *ctx, t_command *cmd)
{
	int	status;
	int	stdin_copy;
	int	stdout_copy;

	if (!save_original_fds(&stdin_copy, &stdout_copy))
		return (1);
	if (!apply_redirections(cmd))
		return (restore_original_fds(stdin_copy, stdout_copy), 1);
	status = 1;
	if (ft_strncmp(cmd->args[0], "cd", __INT_MAX__) == 0)
		status = builtin_cd(ctx, cmd);
	else if (ft_strncmp(cmd->args[0], "echo", __INT_MAX__) == 0)
		status = builtin_echo(ctx, cmd);
	else if (ft_strncmp(cmd->args[0], "env", __INT_MAX__) == 0)
		status = builtin_env(ctx, cmd);
	else if (ft_strncmp(cmd->args[0], "exit", __INT_MAX__) == 0)
		status = builtin_exit(ctx, cmd);
	else if (ft_strncmp(cmd->args[0], "export", __INT_MAX__) == 0)
		status = builtin_export(ctx, cmd);
	else if (ft_strncmp(cmd->args[0], "pwd", __INT_MAX__) == 0)
		status = builtin_pwd();
	else if (ft_strncmp(cmd->args[0], "unset", __INT_MAX__) == 0)
		status = builtin_unset(ctx, cmd);
	restore_original_fds(stdin_copy, stdout_copy);
	return (status);
}

/**
 * @brief Checks if a command is a built-in
 *
 * @param cmd_name Command name to check
 * @return bool true if built-in, false otherwise
 */
bool	is_builtin_command(char *cmd_name)
{
	if (!cmd_name)
		return (false);
	if (ft_strncmp(cmd_name, "exit", __INT_MAX__) == 0)
		return (true);
	if (ft_strncmp(cmd_name, "echo", __INT_MAX__) == 0)
		return (true);
	if (ft_strncmp(cmd_name, "cd", __INT_MAX__) == 0)
		return (true);
	if (ft_strncmp(cmd_name, "pwd", __INT_MAX__) == 0)
		return (true);
	if (ft_strncmp(cmd_name, "export", __INT_MAX__) == 0)
		return (true);
	if (ft_strncmp(cmd_name, "unset", __INT_MAX__) == 0)
		return (true);
	if (ft_strncmp(cmd_name, "env", __INT_MAX__) == 0)
		return (true);
	return (false);
}
