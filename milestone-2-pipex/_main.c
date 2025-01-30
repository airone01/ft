/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:08:58 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/30 15:54:19 by elagouch         ###   ########.fr       */
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
	// Check args and open entry and exit files
	args_valid(&app, argc, argv);
	// Read the commands and arguments from the cli params
	populate_cmds(&app, argc, argv, envp);
	// Open the pipes and store the file descriptors
	fds_open(&app);
	// Execute the commands
	// Free the app structure and exit
	app_free(app);
	return (0);
}
