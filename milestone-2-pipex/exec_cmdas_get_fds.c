/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmdas_get_fds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 18:01:10 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/30 18:10:07 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Gets the input file descriptor for a command
 */
int	get_fd_in(t_app app, t_list *fd_pipes, int cmd_index)
{
	if (cmd_index == 0)
		return (app.fd_file_in);
	if (!fd_pipes || !fd_pipes->content)
		return (-1);
	return (((int *)fd_pipes->content)[0]);
}

/**
 * @brief	Gets the output file descriptor for a command
 */
int	get_fd_out(t_app app, t_list *fd_pipes, int cmd_index, int cmd_count)
{
	if (cmd_index == cmd_count - 1)
		return (app.fd_file_out);
	if (!fd_pipes || !fd_pipes->content)
		return (-1);
	return (((int *)fd_pipes->content)[1]);
}
