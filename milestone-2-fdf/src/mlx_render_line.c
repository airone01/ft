/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render_line.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:40:05 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/24 17:47:15 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Draws a line to the right neighbor if within bounds
 */
static void	draw_right_line(t_app *app, t_point current, int x, int y)
{
	t_point	right;

	if (x >= app->map.width - 1)
		return ;
	right = get_projected_point(x + 1, y, app);
	if (is_line_outside_viewport(current, right, app->img.width,
			app->img.height))
		return ;
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
	if (is_line_outside_viewport(current, down, app->img.width,
			app->img.height))
		return ;
	draw_line_img(app, current, down, color_get_line(app, app->map.matrix[y][x],
			app->map.matrix[y + 1][x]));
}

void	draw_lines(t_app *app)
{
	t_point	current;
	int		x;
	int		y;

	y = 0;
	while (y < app->map.height)
	{
		x = 0;
		while (x < app->map.width)
		{
			current = get_projected_point(x, y, app);
			if (!is_point_in_viewport(current, app->img.width, app->img.height)
				&& !is_point_in_viewport(right, app->img.width,
					app->img.height))
				continue ;
			draw_right_line(app, current, x, y);
			draw_down_line(app, current, x, y);
			x++;
		}
		y++;
	}
}
