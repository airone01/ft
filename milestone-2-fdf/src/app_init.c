/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:12:48 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/13 16:32:17 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

t_app	*app_init(void)
{
	t_app	*app;

	app = safe_calloc(NULL, 1, sizeof(t_app));
	app->map.height = -1;
	app->map.width = -1;
	app->map.matrix = NULL;
	app->win = NULL;
	app->file_fd = -1;
	return (app);
}
