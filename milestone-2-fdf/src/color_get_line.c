/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_get_line.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:03:25 by elagouch          #+#    #+#             */
/*   Updated: 2025/03/05 12:37:09 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Calculate color for line between two points
 *
 * @param p Parameters
 */
unsigned int	color_get_line(t_color_get_line_params p)
{
	int	avg_z;

	if (p.color1 || p.color2)
	{
		if (p.color1 && p.color2)
			return (average_color(p.color1, p.color2));
		else if (p.color1)
			return (p.color1);
		else
			return (p.color2);
	}
	else
	{
		avg_z = (p.z1 + p.z2) / 2;
		return (color_get_by_scheme(avg_z, p.ctx->map.min_elevation,
				p.ctx->map.max_elevation, p.ctx->color_scheme));
	}
}
