/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_next_frame.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:22:41 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/20 14:55:42 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/**
 * Main rendering function that draws the map to the image buffer
 *
 * @param	app	Application context
 */
static void	render_map_frame(t_app *app)
{
	int		x;
	int		y;
	t_point	current;
	t_point	right;
	t_point	down;

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
			current = iso_project((t_point3d){x * app->scale, y * app->scale,
					app->map.matrix[y][x] * app->z_scale});
			current = point_add(current, (t_point){app->offset_x,
					app->offset_y});
			if (x < app->map.width - 1)
			{
				right = iso_project((t_point3d){(x + 1) * app->scale, y
						* app->scale, app->map.matrix[y][x + 1]
						* app->z_scale});
				right = point_add(right, (t_point){app->offset_x,
						app->offset_y});
				draw_line_img(app, current, right,
					color_get(app->map.matrix[y][x], app->map.matrix[y][x
						+ 1]));
			}
			if (y < app->map.height - 1)
			{
				down = iso_project((t_point3d){x * app->scale, (y + 1)
						* app->scale, app->map.matrix[y + 1][x]
						* app->z_scale});
				down = point_add(down, (t_point){app->offset_x, app->offset_y});
				draw_line_img(app, current, down,
					color_get(app->map.matrix[y][x], app->map.matrix[y
						+ 1][x]));
			}
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
	render_map_frame(app);
	mlx_put_image_to_window(app->mlx, app->win, app->img.img, 0, 0);
	return (0);
}
