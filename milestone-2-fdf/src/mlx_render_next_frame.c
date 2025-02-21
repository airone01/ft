/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_next_frame.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:22:41 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 23:02:22 by elagouch         ###   ########.fr       */
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
 * Draws a line to the right neighbor if within bounds
 */
static void	draw_right_line(t_app *app, t_point current, int x, int y)
{
	t_point	right;

	if (x >= app->map.width - 1)
		return ;
	right = get_projected_point(x + 1, y, app);
	draw_line_img(app, current, right, color_get_line(app,
			app->map.matrix[y][x], app->map.matrix[y][x + 1]));
}

/**
 * Draws a line to the downward neighbor if within bounds
 */
static void	draw_down_line(t_app *app, t_point current, int x, int y)
{
	t_point	down;

	if (y >= app->map.height - 1)
		return ;
	down = get_projected_point(x, y + 1, app);
	draw_line_img(app, current, down, color_get_line(app, app->map.matrix[y][x],
			app->map.matrix[y + 1][x]));
}

/**
 * Main rendering function that draws the map to the image buffer
 *
 * @param	app	Application context
 */
static void	render_map_frame(t_app *app)
{
	t_point	current;
	int		x;
	int		y;

	if (app->img.img)
		mlx_destroy_image(app->mlx, app->img.img);
	app->img.img = mlx_new_image(app->mlx, app->img.width, app->img.height);
	app->img.addr = mlx_get_data_addr(app->img.img, &app->img.bits_per_pixel,
			&app->img.line_length, &app->img.endian);
	y = 0;
	while (y < app->map.height)
	{
		x = 0;
		while (x < app->map.width)
		{
			current = get_projected_point(x, y, app);
			draw_right_line(app, current, x, y);
			draw_down_line(app, current, x, y);
			x++;
		}
		y++;
	}
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
	render_map_frame(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img.img, 0, 0);
	app->needs_render = false;
	return (0);
}
