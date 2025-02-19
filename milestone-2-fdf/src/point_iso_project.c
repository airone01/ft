/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_iso_project.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:31:25 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/19 14:52:06 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/**
 * @brief	Project a 3D point to a 2D point using isometric projection
 *
 * @param	p	3D point
 *
 * @return	t_point	2D point
 *
 * @note	The arbitrary angle of 30 degrees is used for the isometric
 * 			projection
 */
t_point	iso_project(t_point3d p)
{
	t_point	result;

	result.x = (p.x - p.y) * cos(0.523599);
	result.y = -p.z + (p.x + p.y) * sin(0.523599);
	return (result);
}
