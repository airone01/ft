/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 19:13:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 21:13:50 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static unsigned int	get_more_rgb_values(double h, double c, double x, double m);

static unsigned int	get_rgb_values(double h, double c, double x, double m)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (h >= 0 && h < 60)
	{
		r = (unsigned int)((c + m) * 255);
		g = (unsigned int)((x + m) * 255);
		b = (unsigned int)(m * 255);
	}
	else if (h >= 60 && h < 120)
	{
		r = (unsigned int)((x + m) * 255);
		g = (unsigned int)((c + m) * 255);
		b = (unsigned int)(m * 255);
	}
	else if (h >= 120 && h < 180)
	{
		r = (unsigned int)(m * 255);
		g = (unsigned int)((c + m) * 255);
		b = (unsigned int)((x + m) * 255);
	}
	else
		return (get_more_rgb_values(h, c, x, m));
	return ((r << 16) | (g << 8) | b);
}

static unsigned int	get_more_rgb_values(double h, double c, double x, double m)
{
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;

	if (h >= 180 && h < 240)
	{
		r = (unsigned int)(m * 255);
		g = (unsigned int)((x + m) * 255);
		b = (unsigned int)((c + m) * 255);
	}
	else if (h >= 240 && h < 300)
	{
		r = (unsigned int)((x + m) * 255);
		g = (unsigned int)(m * 255);
		b = (unsigned int)((c + m) * 255);
	}
	else
	{
		r = (unsigned int)((c + m) * 255);
		g = (unsigned int)(m * 255);
		b = (unsigned int)((x + m) * 255);
	}
	return ((r << 16) | (g << 8) | b);
}

/**
 * @brief	Converts an HSV color to an RGB color
 *
 * @param	h	Hue value
 * @param	s	Saturation value
 * @param	v	Value value
 *
 * @returns	unsigned int	32-bit RGB color
 */
unsigned int	hsv_to_rgb(double h, double s, double v)
{
	double	c;
	double	x;
	double	m;

	c = v * s;
	x = c * (1 - fabs(fmod(h / 60.0, 2) - 1));
	m = v - c;
	return (get_rgb_values(h, c, x, m));
}
