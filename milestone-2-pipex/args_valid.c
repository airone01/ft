/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:32:34 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 14:44:51 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "pipex_mandatory.h"

/**
 * Checks if the arguments are valid and populates the file descriptors
 *
 * @param	app		The app structure
 * @param	argc	Number of arguments
 * @param	argv	Arguments
 */
int	args_valid(t_app *app, int argc, char **argv)
{
	if (argc != 5)
		app_exit_errno(*app, EINVAL);
	app->fd_file_in = open(argv[1], O_RDONLY);
	if (app->fd_file_in == -1)
		app_exit(*app);
	app->fd_file_out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (app->fd_file_out == -1)
		app_exit(*app);
	return (0);
}
