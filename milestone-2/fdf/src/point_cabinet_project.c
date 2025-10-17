/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_cabinet_project.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:00:59 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/25 16:01:49 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Project a 3D point to a 2D point using cabinet projection
 *
 * @param p 3D point
 * @return t_point 2D point
 * @note Cabinet projection shows the front face in true size and shape,
 * with the depth axis shortened by half and shown at a 45 degree angle
 */
t_point	cabinet_project(t_point3d p)
{
	t_point	result;
	double	alpha;

	alpha = M_PI / 4.0;
	result.x = p.x - 0.5 * p.z * cos(alpha);
	result.y = p.y - 0.5 * p.z * sin(alpha);
	return (result);
}
