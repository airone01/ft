/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:12:57 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/29 19:52:23 by elagouch         ###   ########.fr       */
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

static void	free_cmdas(t_app *app)
{
	t_list	*tmp;
	char	**args;
	int		i;

	while (app->cmdas)
	{
		tmp = app->cmdas->next;
		args = (char **)app->cmdas->content;
		i = 0;
		while (args && args[i])
		{
			free(args[i]);
			i++;
		}
		free(app->cmdas->content);
		free(app->cmdas);
		app->cmdas = tmp;
	}
	app->cmdas = NULL;
}

/**
 * @brief	Frees the whole app structure
 */
void	app_free(t_app app)
{
	if (app.fds[0] != -1)
		close(app.fds[0]);
	if (app.fds[1] != -1)
		close(app.fds[1]);
	free(app.file1);
	free(app.file2);
	free_cmds(app);
	ft_printf("[DEBUG] Advanced commands (b4 free):\n");
	ft_lstiter(app.cmdas, cmda_print);
	free_cmdas(&app);
}
