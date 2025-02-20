/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_get_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:03:25 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/20 19:21:55 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/**
 * @brief	Calculate color for line between two points
 *
 * @param	z1		First z value
 * @param	z2		Second z value
 * @param	min_z	Minimum z value
 * @param	max_z	Maximum z value
 */
unsigned int	color_get_line(t_app *ctx, int z1, int z2)
{
	int	avg_z;

	avg_z = (z1 + z2) / 2;
	return (color_get_by_scheme(avg_z, ctx->map.min_elevation,
			ctx->map.max_elevation, ctx->color_scheme));
}
