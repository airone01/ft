/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 16:08:58 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/10 19:49:40 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Entry point of the program
 */
int	main(int argc, char **argv, char **envp)
{
	t_app	app;

	app = app_new(envp);
	args_valid(&app, (unsigned long)argc, argv);
	populate_cmdas(&app, argc, argv);
	exec_cmdas(app);
	app_free(app);
	return (0);
}
