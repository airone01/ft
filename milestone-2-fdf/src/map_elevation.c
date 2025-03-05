/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_elevation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:55:53 by elagouch          #+#    #+#             */
/*   Updated: 2025/03/05 12:43:41 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief	Reads the minimum and maximum elevation values from the map matrix
 *
 * @param	ctx	Application context
 */
void	find_elevation_bounds(t_app *ctx)
{
	int	min;
	int	max;
	int	x;
	int	y;

	min = INT_MAX;
	max = INT_MIN;
	y = 0;
	while (y < ctx->map.height)
	{
		x = 0;
		while (x < ctx->map.width)
		{
			if (ctx->map.matrix[y][x].elevation < min)
				min = ctx->map.matrix[y][x].elevation;
			if (ctx->map.matrix[y][x].elevation > max)
				max = ctx->map.matrix[y][x].elevation;
			x++;
		}
		y++;
	}
	ctx->map.min_elevation = min;
	ctx->map.max_elevation = max;
}
