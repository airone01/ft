/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bresenham.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:44:12 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/25 09:56:19 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Initializes Bresenham parameters
 *
 * @param line Line coordinates in array form [x0, y0, x1, y1]
 * @param params Output array for parameters [dx, dy, sx, sy, err]
 */
static void	init_bresenham_params(int *line, int *params)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;

	dx = abs(line[2] - line[0]);
	dy = -abs(line[3] - line[1]);
	if (line[0] < line[2])
		sx = 1;
	else
		sx = -1;
	if (line[1] < line[3])
		sy = 1;
	else
		sy = -1;
	params[0] = dx;
	params[1] = dy;
	params[2] = sx;
	params[3] = sy;
	params[4] = dx + dy;
}

/**
 * @brief Core Bresenham algorithm implementation with integer math
 *
 * @param p All parameters needed
 */
static void	draw_bresenham_line(t_bresenham_params p)
{
	int	e2;
	int	x;
	int	y;

	x = p.line[0];
	y = p.line[1];
	while (1)
	{
		process_point(p.ctx, x, y, p.color);
		if (x == p.line[2] && y == p.line[3])
			break ;
		e2 = 2 * p.params[4];
		process_x_step(p, &x, e2);
		process_y_step(p, &y, e2);
		if (x == p.line[2] && y == p.line[3])
			break ;
	}
}

/**
 * @brief Draws a line using optimized integer-only Bresenham algorithm
 *
 * @param ctx Application context
 * @param start Starting point of the line
 * @param end Ending point of the line
 * @param color Color of the line
 */
void	draw_line_img(t_app *ctx, t_point start, t_point end,
		unsigned int color)
{
	int	line[4];
	int	params[5];

	line[0] = (int)round(start.x);
	line[1] = (int)round(start.y);
	line[2] = (int)round(end.x);
	line[3] = (int)round(end.y);
	if (is_line_outside_bounds(ctx, line))
		return ;
	init_bresenham_params(line, params);
	draw_bresenham_line((t_bresenham_params){ctx, line, params, color});
}
