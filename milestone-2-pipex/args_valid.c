/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:32:34 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/30 15:19:40 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Checks if the arguments are valid and populates the file descriptors
 *
 * @param	app		The app structure
 * @param	argc	Number of arguments
 * @param	argv	Arguments
 */
void	args_valid(t_app *app, size_t argc, char **argv)
{
	if (argc < 5)
		app_exit_errno(*app, EINVAL);
	if (argc >= PIPEX_PIPES_MAX + 4)
		app_exit_errno(*app, E2BIG);
	app->fd_file_in = open(argv[1], O_RDONLY);
	if (app->fd_file_in == -1)
		app_exit(*app);
	app->fd_file_out = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (app->fd_file_out == -1)
		app_exit(*app);
}
