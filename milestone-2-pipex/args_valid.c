/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_valid.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 17:32:34 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/29 16:32:29 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Check if the arguments are valid
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
	app->fds[0] = open(argv[1], O_RDONLY);
	if (app->fds[0] == -1)
		app_exit(*app);
	app->fds[1] = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (app->fds[1] == -1)
		app_exit(*app);
}
