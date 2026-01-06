/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_child.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:26:04 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/07 11:46:46 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "execute.h"
#include "free.h"
#include "path.h"
#include "signals.h"

/**
 * @brief Sets up input/output redirection for a command
 *
 * @param fds Input and output file descriptors
 * @return bool true on success, false on error
 */
static bool	setup_io_redirection(t_fds fds)
{
	if (fds.in != -1)
	{
		if (dup2(fds.in, STDIN_FILENO) == -1)
			return (false);
		close(fds.in);
	}
	if (fds.out != -1)
	{
		if (dup2(fds.out, STDOUT_FILENO) == -1)
			return (false);
		close(fds.out);
	}
	return (true);
}

/**
 * @brief Executes a builtin command and exits
 *
 * @param ctx Shell context
 * @param cmd Command to execute
 * @param pids Process ids pointer to free
 */
void	execute_builtin_and_exit(t_ctx *ctx, t_command *cmd, int *pids)
{
	int	status;

	status = execute_builtin(ctx, cmd);
	ctx_clear(ctx);
	free(pids);
	exit(status);
}

/**
 * @brief Executes a command in a child process
 *
 * Handles redirections and executes the command
 *
 * @param ctx Shell context
 * @param cmd Command to execute
 * @param fds Input and output file descriptors
 * @param pids Process ids pointer to free
 */
void	execute_command_in_child(t_ctx *ctx, t_command *cmd, t_fds fds,
		int *pids)
{
	char	*bin_path;
	int		status;

	if (!setup_io_redirection(fds) || !apply_redirections(cmd))
	{
		ctx_clear(ctx);
		free(pids);
		exit(1);
	}
	if (!cmd->args)
		return ;
	if (is_builtin_command(cmd->args[0]))
		execute_builtin_and_exit(ctx, cmd, pids);
	setup_child_signals();
	bin_path = bin_find(ctx, cmd->args[0]);
	if (!bin_path)
	{
		status = ctx->exit_status;
		ctx_clear(ctx);
		free(pids);
		exit(status);
	}
	execve(bin_path, cmd->args, ctx->envp);
	free(bin_path);
	exit(error(cmd->args[0], NULL, ERR_CMD_NOT_FOUND));
}
