/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_cmds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:46:10 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/30 15:18:26 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Populates the list of commands from the arguments
 */
static void	populate_basic_cmds(t_app *app, int argc, char **argv)
{
	t_list	*tmp;

	argc -= 3;
	argv += 2;
	while (argc--)
	{
		tmp = ft_lstnew(*argv);
		if (!tmp)
			app_exit_errno(*app, ENOMEM);
		if (!app->cmds)
			app->cmds = tmp;
		else
			ft_lstadd_back(&app->cmds, tmp);
		argv++;
	}
	return ;
}

/**
 * Populates the list of commands from the arguments
 *
 * @param argc	Number of arguments
 * @param argv	Arguments
 * @param envp	Environment variables
 *
 * @returns		A list of commands
 *
 * @exception	ENOMEM if malloc fails
 */
void	populate_cmds(t_app *app, int argc, char **argv, char **envp)
{
	populate_basic_cmds(app, argc, argv);
	cmds_to_cmdas(app, envp);
}
