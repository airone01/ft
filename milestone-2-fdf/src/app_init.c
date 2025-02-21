/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 23:12:48 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 20:18:27 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	app_init_img(t_app *app)
{
	app->img.addr = NULL;
	app->img.img = NULL;
	app->img.bits_per_pixel = 0;
	app->img.line_length = 0;
	app->img.endian = 0;
	app->img.width = IMG_WIDTH;
	app->img.height = IMG_HEIGHT;
	app->offset_x = app->img.width / 2;
	app->offset_y = app->img.height / 3;
}

/**
 * @brief	Initialize the global app structure.
 */
t_app	*app_init(void)
{
	t_app	*app;

	app = safe_calloc(NULL, 1, sizeof(t_app));
	app->map.min_elevation = 0;
	app->map.max_elevation = 0;
	app->needs_render = true;
	app->map.matrix = NULL;
	app->color_scheme = 0;
	app->map.height = -1;
	app->map.width = -1;
	app->z_scale = 1.0;
	app->file_fd = -1;
	app->scale = 20.0;
	app->rot_x = 0.0;
	app->rot_y = 0.0;
	app->rot_z = 0.0;
	app->mlx = NULL;
	app->win = NULL;
	app_init_img(app);
	return (app);
}
