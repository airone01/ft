/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_cmdas.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:46:10 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/31 16:30:18 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Populates the list of commands from the arguments
 *
 * @param argc	Number of arguments
 * @param argv	Arguments
 *
 * @returns		A list of commands
 *
 * @exception	ENOMEM if malloc fails
 */
void	populate_cmdas(t_app *app, int argc, char **argv)
{
	t_list	*tmp;
	char	**args;

	argc -= 3;
	argv += 2;
	while (argc--)
	{
		args = cmda_args(app, *argv);
		tmp = ft_lstnew(args);
		if (!tmp)
		{
			free_strings(args);
			app_exit_errno(*app, ENOMEM);
		}
		if (app->cmdas)
			ft_lstadd_back(&app->cmdas, tmp);
		else
			app->cmdas = tmp;
		argv++;
	}
}
