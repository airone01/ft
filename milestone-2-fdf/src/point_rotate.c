/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_rotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:45:30 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 10:31:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief	Rotate a point around the origin by a given angle.
 *
 * @param	p		The point to rotate.
 * @param	angle	The angle to rotate the point by.
 *
 * @return	t_point	The rotated point.
 */
t_point	point_rotate(t_point p, double angle)
{
	t_point	result;
	double	cos_a;
	double	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	result.x = p.x * cos_a - p.y * sin_a;
	result.y = p.x * sin_a + p.y * cos_a;
	return (result);
}
