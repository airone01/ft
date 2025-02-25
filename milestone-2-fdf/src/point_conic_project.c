/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_conic_project.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:12:46 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/25 16:17:23 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Project a 3D point to a 2D point using conic projection
 *
 * @param p 3D point
 * @param ctx Application context for parameters
 * @return t_point	2D point
 * @note Conic projection creates a perspective effect with a vanishing point
 */
t_point	conic_project(t_point3d p, t_app *ctx)
{
	t_point	result;
	double	z_factor;
	double	distance;

	distance = ctx->horizon_distance;
	if (fuzzy_equals(p.z + distance, 0.0))
		z_factor = 1.0;
	else
		z_factor = distance / (p.z + distance);
	result.x = p.x * z_factor;
	result.y = p.y * z_factor;
	return (result);
}
