/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 15:24:15 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 18:18:49 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "execute.h"

/**
 * @brief Counts commands in a pipeline
 *
 * @param cmd Command list
 * @return int Number of commands
 */
int	count_commands(t_command *cmd)
{
	t_command	*current;
	int			count;

	count = 0;
	current = cmd;
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

/**
 * @brief Cleans up pipe file descriptors
 *
 * @param prev_pipe_read Previous pipe read fd
 * @param pipe_fds Current pipe fds
 * @param has_next Whether there's a next command
 */
void	cleanup_pipes(int prev_pipe_read, int pipe_fds[2], int has_next)
{
	if (prev_pipe_read != -1)
		close(prev_pipe_read);
	if (has_next)
	{
		close(pipe_fds[1]);
		prev_pipe_read = pipe_fds[0];
	}
}

/**
 * @brief Waits for child processes to finish and handles exit status
 * Sets appropriate exit status and displays message for terminated children
 *
 * @param ctx Shell context
 * @param pids Array of process IDs
 * @param cmd_count Number of commands
 */
void	wait_for_children(t_ctx *ctx, pid_t *pids, int cmd_count)
{
	int	i;
	int	status;
	int	sig;

	i = 0;
	status = 0;
	while (i < cmd_count)
	{
		waitpid(pids[i], &status, 0);
		if (i == cmd_count - 1)
		{
			if (WIFEXITED(status))
				ctx->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				sig = WTERMSIG(status);
				ctx->exit_status = 128 + sig;
				if (sig == SIGQUIT)
					write(STDOUT_FILENO, "Quit (core dumped)\n", 19);
			}
		}
		i++;
	}
}

/**
 * @brief Creates a pipe
 *
 * @param pipe_fds Array to store pipe file descriptors
 * @return bool true on success, false on error
 */
bool	create_pipe(int pipe_fds[2])
{
	if (pipe(pipe_fds) == -1)
		return (error("pipe", NULL, ERR_PIPE), false);
	return (true);
}

/**
 * @brief Sets up pipes and handles fork errors
 *
 * @param current Current command
 * @param pipe_fds Pipe file descriptors array
 * @param pids Process IDs array
 * @return bool true if successful, false on error
 */
bool	setup_pipeline_step(t_command *current, int pipe_fds[2], pid_t *pids)
{
	int	i;
	int	cmd_count;

	if (current->next && !create_pipe(pipe_fds))
	{
		i = 0;
		cmd_count = count_commands(current);
		while (i < cmd_count && pids[i] > 0)
			kill(pids[i++], SIGKILL);
		return (false);
	}
	return (true);
}
