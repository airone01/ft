/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmdas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:37:25 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 02:14:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	null_pipes(int *pipe_prev, int *pipe_curr)
{
	pipe_prev[0] = -1;
	pipe_prev[1] = -1;
	pipe_curr[0] = -1;
	pipe_curr[1] = -1;
}

void	exec_cmda_parent(t_list **current_cmd, int *pipe_prev, int *pipe_curr)
{
	if (pipe_prev[0] != -1)
	{
		close(pipe_prev[0]);
		close(pipe_prev[1]);
	}
	if ((*current_cmd)->next)
	{
		pipe_prev[0] = pipe_curr[0];
		pipe_prev[1] = pipe_curr[1];
	}
	*current_cmd = (*current_cmd)->next;
}

static void	main_loop(t_ctx app, t_list *current_cmd, int *pipe_prev,
		int *pipe_curr)
{
	pid_t	pid;

	while (current_cmd)
	{
		if (current_cmd->next)
		{
			if (pipe(pipe_curr) == -1)
				app_exit_errno(app, (unsigned long)errno);
		}
		pid = fork();
		if (pid == -1)
			app_exit_errno(app, (unsigned long)errno);
		if (pid == 0)
			exec_cmda_child(app, current_cmd, pipe_prev, pipe_curr);
		else
			exec_cmda_parent(&current_cmd, pipe_prev, pipe_curr);
	}
}

void	exec_cmdas(t_ctx app)
{
	t_list	*current_cmd;
	int		pipe_prev[2];
	int		pipe_curr[2];

	current_cmd = app.cmdas;
	null_pipes(pipe_prev, pipe_curr);
	main_loop(app, current_cmd, pipe_prev, pipe_curr);
	if (app.fd_file_in != -1)
		close(app.fd_file_in);
	if (app.fd_file_out != -1)
		close(app.fd_file_out);
	while (wait(NULL) > 0)
		;
}
