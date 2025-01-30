/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fds_open.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:25:52 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/30 15:58:51 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	fd_pair_new(t_app *app)
{
	t_list	*pair;
	int		*fds;

	fds = malloc(sizeof(int) * 2);
	if (!fds)
		app_exit_errno(*app, ENOMEM);
	fds[0] = -1;
	fds[1] = -1;
	if (pipe(fds) == -1)
		app_exit_errno(*app, errno);
	pair = ft_lstnew(fds);
	if (!pair)
		app_exit_errno(*app, ENOMEM);
	if (app->fd_pipes)
		ft_lstadd_back(&app->fd_pipes, pair);
	else
		app->fd_pipes = pair;
}

void	fds_open(t_app *app)
{
	size_t	cmds_len;

	cmds_len = ft_lstsize(app->cmdas);
	while (cmds_len--)
	{
		fd_pair_new(app);
	}
}
