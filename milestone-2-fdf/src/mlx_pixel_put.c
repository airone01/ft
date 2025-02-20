/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:00:21 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/20 12:29:52 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/**
 * @brief	Put a pixel to the image
 *
 * @param	img		Image to put the pixel to
 * @param	x		X coordinate of the pixel
 * @param	y		Y coordinate of the pixel
 * @param	color	Color of the pixel
 */
void	my_mlx_pixel_put(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}
