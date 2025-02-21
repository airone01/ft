/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_normalize.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:47:23 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 10:31:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief	Normalize a point
 *
 * @param	p	Point to normalize
 *
 * @returns	t_point	Normalized point
 */
t_point	point_normalize(t_point p)
{
	double	mag;

	mag = point_magnitude(p);
	if (fuzzy_equals(mag, 0.0))
		return (p);
	return (point_scale(p, 1.0 / mag));
}
