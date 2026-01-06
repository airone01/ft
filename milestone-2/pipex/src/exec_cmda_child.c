/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmda_child.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:27:50 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 02:14:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_input(t_ctx app, int *pipe_prev)
{
	if (pipe_prev[0] != -1)
	{
		dup2(pipe_prev[0], STDIN_FILENO);
		close(pipe_prev[0]);
		close(pipe_prev[1]);
	}
	else if (app.fd_file_in != -1)
	{
		dup2(app.fd_file_in, STDIN_FILENO);
		close(app.fd_file_in);
	}
}

static void	handle_output(t_ctx app, t_list *current_cmd, int *pipe_curr)
{
	if (current_cmd->next)
	{
		close(pipe_curr[0]);
		dup2(pipe_curr[1], STDOUT_FILENO);
		close(pipe_curr[1]);
	}
	else if (app.fd_file_out != -1)
	{
		dup2(app.fd_file_out, STDOUT_FILENO);
		close(app.fd_file_out);
	}
}

void	exec_cmda_child(t_ctx app, t_list *current_cmd, int *pipe_prev,
		int *pipe_curr)
{
	char	**args;

	handle_input(app, pipe_prev);
	handle_output(app, current_cmd, pipe_curr);
	args = (char **)current_cmd->content;
	execve(args[0], args, app.envp);
	exit(EXIT_FAILURE);
}
