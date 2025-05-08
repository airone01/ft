/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:44:19 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:00:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"

/**
 * @brief Executes special cases of commands
 *
 * @param ctx Shell context
 * @param cmd Command to execute
 */
static bool	special_cases(t_ctx *ctx, t_command *cmd)
{
	if (cmd->arg_count == 0 && cmd->next == NULL && cmd->args[0]
		&& ft_strncmp(cmd->args[0], ":", 3) == 0)
		return (ctx->exit_status = 0, true);
	if (cmd->arg_count == 0 && cmd->next == NULL && cmd->args[0]
		&& ft_strncmp(cmd->args[0], "!", 3) == 0)
		return (ctx->exit_status = 1, true);
	return (false);
}

/**
 * @brief Handles redirections without any command
 *
 * @param ctx Shell context
 * @param cmd Command structure with redirections
 * @return bool true if redirections were processed, false on error
 */
static bool	handle_redirections_only(t_ctx *ctx, t_command *cmd)
{
	int	stdin_copy;
	int	stdout_copy;

	if (!save_original_fds(&stdin_copy, &stdout_copy))
		return (false);
	if (read_all_heredocs(ctx) != 0)
	{
		cleanup_heredoc_resources(ctx);
		restore_original_fds(stdin_copy, stdout_copy);
		return (false);
	}
	if (!apply_redirections(cmd))
	{
		cleanup_heredoc_resources(ctx);
		restore_original_fds(stdin_copy, stdout_copy);
		return (false);
	}
	restore_original_fds(stdin_copy, stdout_copy);
	cleanup_heredoc_resources(ctx);
	return (true);
}

/**
 * @brief Executes a command or pipeline
 *
 * @param ctx Shell context
 * @param cmd Command to execute
 */
void	execute_commands(t_ctx *ctx, t_command *cmd)
{
	if (!cmd)
		return ;
	if ((!cmd->args || !cmd->args[0]) && cmd->redirection)
	{
		handle_redirections_only(ctx, cmd);
		return ;
	}
	if (!cmd->args || !cmd->args[0])
		return ;
	if (special_cases(ctx, cmd))
		return ;
	if (read_all_heredocs(ctx) != 0)
	{
		cleanup_heredoc_resources(ctx);
		return ;
	}
	if (cmd && !cmd->next && is_builtin_command(cmd->args[0]))
	{
		ctx->exit_status = execute_builtin(ctx, cmd);
		return ;
	}
	execute_pipeline(ctx, cmd);
	cleanup_heredoc_resources(ctx);
}
