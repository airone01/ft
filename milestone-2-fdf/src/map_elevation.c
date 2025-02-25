/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_elevation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 18:55:53 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 21:13:50 by elagouch         ###   ########.fr       */
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
			if (ctx->map.matrix[y][x] < min)
				min = ctx->map.matrix[y][x];
			if (ctx->map.matrix[y][x] > max)
				max = ctx->map.matrix[y][x];
			x++;
		}
		y++;
	}
	ctx->map.min_elevation = min;
	ctx->map.max_elevation = max;
}
