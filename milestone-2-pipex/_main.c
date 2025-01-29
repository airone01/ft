/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:08:58 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/29 16:55:22 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Entry point of the program
 */
int	main(int argc, char **argv, char **envp)
{
	t_app	app;

	(void)argc;
	(void)argv;
	(void)envp;
	app = app_new();
	args_valid(&app, argc, argv);
	populate_cmds(&app, argc, argv, envp);
	ft_lstiter(app.cmds, cmda_print);
	// ft_lstclear(cmda_free); // REMOVED IN NEW VERSION
	app.file1 = file_read(&app, app.fds[0]);
	file_write(&app, app.fds[1], app.file1);
	app_free(app);
	return (0);
}
