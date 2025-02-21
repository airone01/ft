/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bresenham.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:44:12 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 21:13:50 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Initialize line drawing parameters
 *
 * @param	start		Starting point of the line
 * @param	end			Ending point of the line
 * @return	t_line_vars	Line variables for drawing
 */
static t_line_vars	init_line_vars(t_point start, t_point end)
{
	t_line_vars	vars;

	vars.delta.x = end.x - start.x;
	vars.delta.y = end.y - start.y;
	vars.steps = fmax(fabs(vars.delta.x), fabs(vars.delta.y));
	if (vars.steps > 0)
	{
		vars.delta.x /= vars.steps;
		vars.delta.y /= vars.steps;
	}
	vars.current = start;
	return (vars);
}

/**
 * Check if a point is within the image bounds
 *
 * @param	ctx			Application context
 * @param	point		Point to check
 * @return	int			1 if in bounds, 0 otherwise
 */
static int	is_point_in_bounds(t_app *ctx, t_point point)
{
	return (point.x >= 0 && point.x < ctx->img.width && point.y >= 0
		&& point.y < ctx->img.height);
}

/**
 * Draw a line using Bresenham's algorithm and an image buffer
 *
 * @param	ctx			Application context
 * @param	start		Starting point of the line
 * @param	end			Ending point of the line
 * @param	color		Color of the line
 */
void	draw_line_img(t_app *ctx, t_point start, t_point end,
		unsigned int color)
{
	t_line_vars	vars;
	int			i;

	vars = init_line_vars(start, end);
	if (vars.steps < 1 && is_point_in_bounds(ctx, start))
	{
		mlx_pixel_put_img(&ctx->img, (int)round(start.x), (int)round(start.y),
			color);
		return ;
	}
	i = 0;
	while (i <= vars.steps)
	{
		if (is_point_in_bounds(ctx, vars.current))
			mlx_pixel_put_img(&ctx->img, (int)round(vars.current.x),
				(int)round(vars.current.y), color);
		vars.current.x += vars.delta.x;
		vars.current.y += vars.delta.y;
		i++;
	}
}
