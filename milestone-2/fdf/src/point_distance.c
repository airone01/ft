/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:44:53 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 10:31:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief	Calculate the distance between two points
 *
 * @param	a	First point
 * @param	b	Second point
 *
 * @return	The distance between the two points
 */
double	point_distance(t_point a, t_point b)
{
	double	dx;
	double	dy;

	dx = b.x - a.x;
	dy = b.y - a.y;
	return (sqrt(dx * dx + dy * dy));
}
