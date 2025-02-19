/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:12:48 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/19 17:12:47 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/**
 * @brief	Initialize the global app structure.
 */
t_app	*app_init(void)
{
	t_app	*app;

	app = safe_calloc(NULL, 1, sizeof(t_app));
	app->map.height = -1;
	app->map.width = -1;
	app->map.matrix = NULL;
	app->win = NULL;
	app->file_fd = -1;
	app->img.addr = NULL;
	app->img.img = NULL;
	app->img.width = 0;
	app->img.height = 0;
	app->img.bits_per_pixel = 0;
	app->img.line_length = 0;
	app->img.endian = 0;
	app->mlx = NULL;
	return (app);
}
