/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:15:01 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/31 16:13:51 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Initializes the app structure
 */
t_app	app_new(char **envp)
{
	t_app	app;

	app.cmdas = NULL;
	app.fd_file_in = -1;
	app.fd_file_out = -1;
	app.bonus_pipes[0] = -1;
	app.bonus_pipes[1] = -1;
	app.envp = envp;
	return (app);
}
