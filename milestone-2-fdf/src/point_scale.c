/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_scale.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 14:43:03 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/19 14:43:24 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/**
 * @brief	Scales a point
 *
 * @param	p		Point to scale
 * @param	scale	Scale factor
 *
 * @returns	t_point	Result of the scaling
 */
t_point	point_scale(t_point p, double scale)
{
	t_point	result;

	result.x = p.x * scale;
	result.y = p.y * scale;
	return (result);
}
