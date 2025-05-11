/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_bresenham_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 09:55:50 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 19:01:07 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Checks if the line is completely outside valid rendering bounds
 *
 * @param ctx Application context
 * @param line Line coordinates in array form [x0, y0, x1, y1]
 * @return bool True if line is completely outside and can be culled
 */
bool	is_line_outside_bounds(t_app *ctx, int *line)
{
	int	w;
	int	h;

	w = ctx->img.width;
	h = ctx->img.height;
	if ((line[0] < 0 && line[2] < 0) || (line[0] >= w && line[2] >= w))
		return (true);
	if ((line[1] < 0 && line[3] < 0) || (line[1] >= h && line[3] >= h))
		return (true);
	return (false);
}

/**
 * @brief Processes a single point in the Bresenham line
 *
 * @param ctx Application context
 * @param x X-coordinate to render
 * @param y Y-coordinate to render
 * @param color Line color
 */
void	process_point(t_app *ctx, int x, int y, unsigned int color)
{
	if (x >= 0 && x < ctx->img.width && y >= 0 && y < ctx->img.height)
		mlx_pixel_put_img(&ctx->img, x, y, color);
}

/**
 * @brief Process a single step in the Bresenham algorithm for X adjustment
 *
 * @param p Bresenham parameters structure
 * @param x Pointer to x coordinate to update
 * @param e2 Value of error * 2
 */
void	process_x_step(t_bresenham_params p, int *x, int e2)
{
	if (e2 >= p.params[1])
	{
		if (*x == p.line[2])
			return ;
		p.params[4] += p.params[1];
		*x += p.params[2];
	}
}

/**
 * @brief Process a single step in the Bresenham algorithm for Y adjustment
 *
 * @param p Bresenham parameters structure
 * @param y Pointer to y coordinate to update
 * @param e2 Value of error * 2
 */
void	process_y_step(t_bresenham_params p, int *y, int e2)
{
	if (e2 <= p.params[0])
	{
		if (*y == p.line[3])
			return ;
		p.params[4] += p.params[0];
		*y += p.params[3];
	}
}
