/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:32:34 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/10 19:48:50 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	handle_file_opening(t_app *app, int here_doc, unsigned long argc,
		char **argv)
{
	if (here_doc)
	{
		if (ft_strlen(argv[2]) == 0)
			app_exit_errno(*app, EINVAL);
		app->fd_file_in = handle_here_doc(app, argv[2]);
		if (app->fd_file_in == -1)
			app_exit(*app);
		app->fd_file_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND,
				0644);
	}
	else
	{
		app->fd_file_in = open(argv[1], O_RDONLY);
		if (app->fd_file_in == -1)
			app_exit(*app);
		app->fd_file_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC,
				0644);
	}
	if (app->fd_file_out == -1)
		app_exit(*app);
}

/**
 * Checks if the arguments are valid and populates the file descriptors
 *
 * @param	app		The app structure
 * @param	argc	Number of arguments
 * @param	argv	Arguments
 */
int	args_valid(t_app *app, unsigned long argc, char **argv)
{
	int	here_doc;

	if (argc < 5)
		app_exit_errno(*app, EINVAL);
	if (argc >= PIPEX_PIPES_MAX + 4)
		app_exit_errno(*app, E2BIG);
	here_doc = ft_strcmp(argv[1], "here_doc") == 0;
	if (here_doc && argc < 6)
		app_exit_errno(*app, EINVAL);
	handle_file_opening(app, here_doc, argc, argv);
	return (here_doc);
}
