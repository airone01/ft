/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:15:01 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/29 18:22:40 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Initializes the app structure
 */
t_app	app_new(void)
{
	t_app	app;

	app.fds[0] = -1;
	app.fds[1] = -1;
	app.file1 = NULL;
	app.file2 = NULL;
	app.cmds = NULL;
	app.cmdas = NULL;
	return (app);
}
