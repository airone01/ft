/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmdas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:37:25 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/30 16:59:57 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_cmda(t_app app, char **args, int fd_in, int fd_out)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		app_exit_errno(app, errno);
	if (pid == 0)
	{
		if (fd_in != -1)
		{
			if (dup2(fd_in, STDIN_FILENO) == -1)
				app_exit_errno(app, errno);
		}
		if (fd_out != -1)
		{
			if (dup2(fd_out, STDOUT_FILENO) == -1)
				app_exit_errno(app, errno);
		}
		execve(args[0], args, app.envp);
		app_exit_errno(app, errno);
	}
}

/**
 * @brief	Executes the commands one by one
 */
void	exec_cmdas(t_app app)
{
	size_t	cmds_len;
	t_list	*cmdas;
	int		fds[2];
	int		i;

	i = 0;
	cmdas = app.cmdas;
	cmds_len = ft_lstsize(app.cmdas);
	while (cmdas)
	{
		ft_printf("[DEBUG] Executing command no. %d (%s)\n", i,
			((char **)cmdas->content)[0]);
		if (i == 0)
			exec_cmda(app, cmdas->content, app.fd_file_in, -1);
		else if (i == ft_lstsize(app.cmdas) - 1)
			exec_cmda(app, cmdas->content, -1, app.fd_file_out);
		else
			exec_cmda(app, cmdas->content, -1, -1);
		ft_printf("[DEBUG] Executed command no. %d (%s)\n", i,
			((char **)cmdas->content)[0]);
		cmdas = cmdas->next;
		i++;
	}
}
