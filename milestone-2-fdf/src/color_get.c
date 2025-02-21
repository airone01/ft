/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_get.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:35:15 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 21:13:50 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief	Map value to a color using elevation gradient
 *
 * @param	min_z	Mimimum z value
 * @param	max_z	Maximum z value
 *
 * @returns	unsigned int	Color value
 */
unsigned int	color_get(int z, int min_z, int max_z)
{
	double	ratio;
	double	hue;

	if (min_z == max_z)
		return (0x0000FFFF);
	ratio = (double)(z - min_z) / (max_z - min_z);
	if (ratio < 0.25)
		hue = 240 - (ratio * 4 * 60);
	else if (ratio < 0.5)
		hue = 180 - ((ratio - 0.25) * 4 * 60);
	else if (ratio < 0.75)
		hue = 120 - ((ratio - 0.5) * 4 * 60);
	else
		hue = 60 - ((ratio - 0.75) * 4 * 60);
	return (hsv_to_rgb(hue, 0.8, 1.0));
}
