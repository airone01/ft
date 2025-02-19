/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_magnitude.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:46:10 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/19 14:47:08 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/**
 * @brief	Calculate the magnitude of a point using the Pythagorean theorem
 *
 * @param	p		Point to calculate the magnitude
 *
 * @return	double	Magnitude of the point
 */
double	point_magnitude(t_point p)
{
	return (sqrt(p.x * p.x + p.y * p.y));
}
