/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:08:58 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/31 16:46:09 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
Note:	The bonus part of this program includes here_doc, which waits for user
		input until a limiter string is entered. The limiter string is the
		second argument of the program.
		The program WILL leak if the user quits the program before entering the
		limiter string (with Ctrl+C for example).
		This is expected behavior as the signal function is forbidden.
*/

/**
 * @brief	Entry point of the program
 */
int	main(int argc, char **argv, char **envp)
{
	t_app	app;

	app = app_new(envp);
	args_valid(&app, argc, argv);
	argc -= 1;
	argv += 1;
	populate_cmdas(&app, argc, argv);
	exec_cmdas(app);
	app_free(app);
	return (0);
}
