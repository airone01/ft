/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_free_fd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:42:53 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/30 16:20:11 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Frees the file descriptors and pipes
 * This is mostly useful for getting rid of a warning in Valgrind
 *
 * @param	app		The app structure
 */
static void	free_fd_if_valid(int *fd)
{
	if (*fd != -1)
	{
		close(*fd);
		*fd = -1;
	}
}

static void	free_fd_pair(void *content)
{
	int	*fd_pair;

	fd_pair = (int *)content;
	free_fd_if_valid(&fd_pair[0]);
	free_fd_if_valid(&fd_pair[1]);
	free(fd_pair);
}

// static void	debug_fd_pair(void *content)
// {
// 	int	*fd_pair;

// 	fd_pair = (int *)content;
// 	printf("fd_pair[0] = %d\n", fd_pair[0]);
// 	printf("fd_pair[1] = %d\n", fd_pair[1]);
// }

/**
 * @brief	Frees the file descriptors and pipes
 *
 * @param	app		The app structure
 */
void	free_fds(t_app app)
{
	free_fd_if_valid(&app.fd_file_in);
	free_fd_if_valid(&app.fd_file_out);
	ft_lstclear(&app.fd_pipes, free_fd_pair);
}
