/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_next_frame.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:22:41 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/24 17:40:21 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Helper function to project a 3D point to 2D with scaling and offset
 */
static t_point	get_projected_point(int x, int y, t_app *app)
{
	t_point3d	point3d;
	t_point		projected;

	point3d.x = x * app->scale;
	point3d.y = y * app->scale;
	point3d.z = app->map.matrix[y][x] * app->z_scale;
	point3d = rotate_x(point3d, app->rot_x);
	point3d = rotate_y(point3d, app->rot_y);
	point3d = rotate_z(point3d, app->rot_z);
	projected = iso_project(point3d);
	projected = point_add(projected, (t_point){app->offset_x, app->offset_y});
	return (projected);
}

/**
 * @brief	Renders the next frame
 *
 * @param	app	Application context
 */
int	render_next_frame(t_app *app)
{
	if (!app->needs_render)
		return (0);
	if (!app->img.img)
	{
		app->img.img = mlx_new_image(app->mlx, app->img.width, app->img.height);
		app->img.addr = mlx_get_data_addr(app->img.img,
				&app->img.bits_per_pixel, &app->img.line_length,
				&app->img.endian);
		ft_memset(app->img.addr, 0, (size_t)(app->img.height
				* app->img.line_length));
	}
	else
		ft_memset(app->img.addr, 0, (size_t)(app->img.height
				* app->img.line_length));
	draw_lines(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img.img, 0, 0);
	app->needs_render = false;
	return (0);
}
