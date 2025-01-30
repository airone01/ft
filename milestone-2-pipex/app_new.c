/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:15:01 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/30 18:56:44 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Initializes the app structure
 */
t_app	app_new(char **envp)
{
	t_app	app;

	app.cmds = NULL;
	app.cmdas = NULL;
	app.fd_file_in = -1;
	app.fd_file_out = -1;
	app.envp = envp;
	return (app);
}
