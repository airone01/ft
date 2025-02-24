/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_pixel_put.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:00:21 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/24 17:15:50 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief	Put a pixel to the image
 *
 * @param	img		Image to put the pixel to
 * @param	x		X coordinate of the pixel
 * @param	y		Y coordinate of the pixel
 * @param	color	Color of the pixel
 */
void	mlx_pixel_put_img(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;
	int		pixel_pos;

	if (!img || !img->addr || x < 0 || x >= img->width || y < 0
		|| y >= img->height)
		return ;
	pixel_pos = y * img->line_length + x * (img->bits_per_pixel / 8);
	if (pixel_pos < 0 || pixel_pos >= (img->height * img->line_length))
		return ;
	dst = img->addr + pixel_pos;
	*(unsigned int *)dst = color;
}
