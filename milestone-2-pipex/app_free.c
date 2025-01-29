/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:12:57 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/29 18:40:17 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_cmds(t_app app)
{
	t_list	*ptr;
	t_list	*tmp;

	ptr = app.cmds;
	while (ptr)
	{
		tmp = ptr->next;
		free(ptr);
		ptr = tmp;
	}
	app.cmds = NULL;
}

/**
 * @brief	Frees the whole app structure
 */
void	app_free(t_app app)
{
	t_list	**cmdas;

	cmdas = &app.cmdas;
	if (app.fds[0] != -1)
		close(app.fds[0]);
	if (app.fds[1] != -1)
		close(app.fds[1]);
	free(app.file1);
	free(app.file2);
	free_cmds(app);
	if (app.cmds)
		ft_lstclear(&app.cmdas, (void (*)(void *))free_strings);
}
