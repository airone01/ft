/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmdas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:37:25 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/30 18:54:33 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_fd_if_valid(int fd)
{
	if (fd > 2)
		close(fd);
}

static void	close_pipe(int pipe_fds[2])
{
	close_fd_if_valid(pipe_fds[0]);
	close_fd_if_valid(pipe_fds[1]);
}

static void	execute_child(t_app app, char **args, int fd_in, int fd_out)
{
	char	*bin_path;

	if (fd_in != STDIN_FILENO)
	{
		if (dup2(fd_in, STDIN_FILENO) == -1)
			app_exit(app);
		close_fd_if_valid(fd_in);
	}
	if (fd_out != STDOUT_FILENO)
	{
		if (dup2(fd_out, STDOUT_FILENO) == -1)
			app_exit(app);
		close_fd_if_valid(fd_out);
	}
	bin_path = args[0];
	args++;
	if (execve(bin_path, args, app.envp) == -1)
		app_exit(app);
}

static void	execute_first_command(t_app app, char **cmd, int pipe_fds[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		app_exit(app);
	if (pid == 0)
	{
		close_fd_if_valid(pipe_fds[0]);
		execute_child(app, cmd, app.fd_file_in, pipe_fds[1]);
	}
}

static void	execute_last_command(t_app app, char **cmd, int prev_pipe[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		app_exit(app);
	if (pid == 0)
	{
		close_fd_if_valid(prev_pipe[1]);
		execute_child(app, cmd, prev_pipe[0], app.fd_file_out);
	}
}

static void	execute_middle_command(t_app app, char **cmd, int prev_pipe[2],
		int next_pipe[2])
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		app_exit(app);
	if (pid == 0)
	{
		close_fd_if_valid(prev_pipe[1]);
		close_fd_if_valid(next_pipe[0]);
		execute_child(app, cmd, prev_pipe[0], next_pipe[1]);
	}
	else
		wait(NULL);
}

void	exec_cmdas(t_app app)
{
	t_list	*current_cmd;
	t_list	*current_pipe;
	int		cmd_index;
	int		*curr_pipe;
	int		*prev_pipe;

	current_cmd = app.cmdas;
	current_pipe = app.fd_pipes;
	cmd_index = 0;
	while (current_cmd)
	{
		curr_pipe = NULL;
		if (current_pipe)
			curr_pipe = current_pipe->content;
		if (cmd_index == 0)
			execute_first_command(app, current_cmd->content, curr_pipe);
		else if (!current_cmd->next)
			execute_last_command(app, current_cmd->content, prev_pipe);
		else
			execute_middle_command(app, current_cmd->content, prev_pipe,
				curr_pipe);
		prev_pipe = curr_pipe;
		current_cmd = current_cmd->next;
		if (current_pipe)
			current_pipe = current_pipe->next;
		else
			current_pipe = NULL;
		cmd_index++;
	}
	// Close all pipes in parent
	current_pipe = app.fd_pipes;
	while (current_pipe)
	{
		close_pipe(current_pipe->content);
		current_pipe = current_pipe->next;
	}
	// Wait for all children
	while (cmd_index--)
		wait(NULL);
}

in = open(file1);

pipe_magick(in, ...)
