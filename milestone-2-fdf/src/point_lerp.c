/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_lerp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:48:42 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 10:31:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief	Linear interpolation between two points
 *
 * @param	a	First point
 * @param	b	Second point
 * @param	t	Interpolation factor
 *
 * @return	t_point	Interpolated point
 */
t_point	point_lerp(t_point a, t_point b, double t)
{
	t_point	result;

	result.x = a.x + (b.x - a.x) * t;
	result.y = a.y + (b.y - a.y) * t;
	return (result);
}
