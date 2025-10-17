/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_get_by_scheme.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:04:13 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 21:13:50 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned int	color_get_more_by_scheme(int z, int min_z, int max_z,
						int scheme);

/**
 * @brief	Sets a color scheme
 *
 * @param	z		Elevation value
 * @param	min_z	Minimum elevation value
 * @param	max_z	Maximum elevation value
 * @param	scheme	Color scheme to use
 */
unsigned int	color_get_by_scheme(int z, int min_z, int max_z, int scheme)
{
	unsigned int	val;
	double			ratio;

	if (scheme == 0)
		return (color_get(z, min_z, max_z));
	if (scheme == 1)
	{
		ratio = (double)(z - min_z) / (max_z - min_z);
		val = (unsigned int)(ratio * 255);
		return ((val << 16) | (val << 8) | val);
	}
	return (color_get_more_by_scheme(z, min_z, max_z, scheme));
}

static unsigned int	color_get_more_by_scheme(int z, int min_z, int max_z,
		int scheme)
{
	unsigned int	green;
	unsigned int	blue;
	double			ratio;

	if (scheme == 2)
	{
		ratio = (double)(z - min_z) / (max_z - min_z);
		return (hsv_to_rgb(ratio * 360, 0.8, 1.0));
	}
	if (scheme == 3)
	{
		ratio = (double)(z - min_z) / (max_z - min_z);
		blue = 200 + (unsigned int)(ratio * 55);
		green = (unsigned int)(ratio * 200);
		return ((0 << 16) | (green << 8) | blue);
	}
	return (0x00FFFFFF);
}
