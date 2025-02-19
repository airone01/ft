/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_dot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:44:01 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/19 14:44:35 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/**
 * @brief	Calculate the dot product of two points
 *
 * @param	a	First point
 * @param	b	Second point
 *
 * @return	double	The dot product of the two points
 */
double	point_dot(t_point a, t_point b)
{
	return (a.x * b.x + a.y * b.y);
}
