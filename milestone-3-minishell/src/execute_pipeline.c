/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 16:45:37 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/08 17:01:45 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "execute.h"
#include "signals.h"

/**
 * @brief Handles fork failures and resource cleanup
 *
 * @param current Current command
 * @param pipe_fds Pipe file descriptors
 * @param prev_pipe_read Previous pipe read end
 * @param pids Process IDs array
 * @return bool true if successful, false on error
 */
static bool	handle_fork_error(t_command *current, int pipe_fds[2],
		int prev_pipe_read, pid_t *pids)
{
	int	i;
	int	cmd_count;

	if (current->next)
	{
		close(pipe_fds[0]);
		close(pipe_fds[1]);
	}
	if (prev_pipe_read != -1)
		close(prev_pipe_read);
	i = 0;
	cmd_count = count_commands(current);
	while (i < cmd_count && pids[i] > 0)
		kill(pids[i++], SIGKILL);
	return (false);
}

/**
 * @brief Initializes pipeline execution resources
 *
 * Allocates memory for process IDs and sets up initial values
 *
 * @param cmd Command list
 * @param pids Pointer to store process IDs array
 * @return t_pipeline_init Pipeline initialization data
 */
static t_pipeline_init	init_pipeline(t_command *cmd, pid_t **pids)
{
	t_pipeline_init	init;

	init.cmd_count = count_commands(cmd);
	*pids = (pid_t *)malloc(sizeof(pid_t) * (unsigned long)init.cmd_count);
	if (!*pids)
		return ((t_pipeline_init){NULL, -1, 0, 0});
	init.current = cmd;
	init.prev_pipe_read = -1;
	init.i = 0;
	setup_parent_signals();
	return (init);
}

/**
 * @brief Handles child process execution in pipeline
 *
 * Configures file descriptors and executes the command
 *
 * @param ctx Shell context
 * @param current Current command
 * @param pipe_fds Pipe file descriptors
 * @param pipeline Pipeline execution data
 */
static void	handle_child_process(t_ctx *ctx, t_command *current,
		int pipe_fds[2], t_pipeline *pipeline)
{
	int	my_fd;

	my_fd = -1;
	if (current->next)
	{
		my_fd = pipe_fds[1];
		close(pipe_fds[0]);
	}
	execute_command_in_child(ctx, current, (t_fds){pipeline->prev_pipe_read,
		my_fd}, pipeline->pids);
}

/**
 * @brief Executes a single pipeline step
 *
 * Creates pipes, forks a process and handles execution
 *
 * @param ctx Shell context
 * @param current Current command
 * @param pipeline Pipeline execution data
 * @return bool true if successful, false on error
 */
static bool	execute_pipeline_step(t_ctx *ctx, t_command *current,
		t_pipeline *pipeline)
{
	int	pipe_fds[2];

	if (!setup_pipeline_step(current, pipe_fds, pipeline->pids))
		return (false);
	pipeline->pids[pipeline->i] = fork();
	if (pipeline->pids[pipeline->i] == -1)
	{
		handle_fork_error(current, pipe_fds, pipeline->prev_pipe_read,
			pipeline->pids);
		return (false);
	}
	if (pipeline->pids[pipeline->i] == 0)
		handle_child_process(ctx, current, pipe_fds, pipeline);
	cleanup_pipes(pipeline->prev_pipe_read, pipe_fds, current->next != NULL);
	if (current->next)
		pipeline->prev_pipe_read = pipe_fds[0];
	return (true);
}

/**
 * @brief Executes a pipeline of commands
 *
 * Creates pipes, forks processes, and waits for completion
 *
 * @param ctx Shell context
 * @param cmd Command list
 */
void	execute_pipeline(t_ctx *ctx, t_command *cmd)
{
	t_command		*current;
	t_pipeline		pipeline;
	t_pipeline_init	init;

	init = init_pipeline(cmd, &pipeline.pids);
	if (!pipeline.pids)
		return ;
	signal(SIGINT, SIG_IGN);
	current = init.current;
	pipeline.prev_pipe_read = init.prev_pipe_read;
	pipeline.i = init.i;
	while (current)
	{
		if (!execute_pipeline_step(ctx, current, &pipeline))
		{
			free(pipeline.pids);
			return ;
		}
		current = current->next;
		pipeline.i++;
	}
	wait_for_children(ctx, pipeline.pids, init.cmd_count);
	free(pipeline.pids);
	setup_interactive_signals();
}
