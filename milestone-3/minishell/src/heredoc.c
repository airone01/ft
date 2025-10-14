/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:30:10 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 17:56:38 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "execute.h"
#include "globals.h"
#include "signals.h"

static void	restore_shell_state(void)
{
	reset_heredoc_state();
	setup_interactive_signals();
	rl_event_hook = NULL;
	g_signal_status = 0;
}

static int	create_heredoc(t_ctx *ctx, char *delimiter)
{
	int	pipe_fds[2];
	int	read_fd;
	int	result;

	g_signal_status = 0;
	if (pipe(pipe_fds) == -1)
		return (error(NULL, "heredoc", ERR_PIPE));
	setup_heredoc_signals();
	result = read_heredoc_content(pipe_fds, delimiter, ctx);
	close(pipe_fds[1]);
	if (result == -1 || is_heredoc_interrupted())
	{
		close(pipe_fds[0]);
		if (is_heredoc_interrupted())
		{
			ctx->exit_status = 130;
			g_signal_status = 0;
		}
		restore_shell_state();
		return (-1);
	}
	read_fd = pipe_fds[0];
	restore_shell_state();
	return (read_fd);
}

/**
 * @brief Reads heredoc content for all commands in a pipeline
 *
 * @param ctx Context containing environment information
 * @return int 0 on success, -1 on error
 */
int	read_all_heredocs(t_ctx *ctx)
{
	t_command	*current;
	t_redir		*redir;
	int			heredoc_fd;

	current = ctx->cmd;
	while (current)
	{
		redir = current->redirection;
		while (redir)
		{
			if (redir->type == TOK_HERE_DOC_FROM)
			{
				heredoc_fd = create_heredoc(ctx, redir->filename);
				if (heredoc_fd == -1)
					return (-1);
				redir->fd = heredoc_fd;
			}
			redir = redir->next;
		}
		current = current->next;
	}
	return (0);
}
