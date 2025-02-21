/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:44:12 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 10:31:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/* Helper function to put a pixel in the image buffer */
static void	put_pixel_to_img(t_img *img, int x, int y, unsigned int color)
{
	char	*dst;

	if (x >= 0 && x < img->width && y >= 0 && y < img->height)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel
					/ 8));
		*(unsigned int *)dst = color;
	}
}

/**
 * Better implementation of Bresenham's line algorithm using an image buffer
 * instead of drawing directly to the window with `mlx_pixel_put`.
 *
 * @param	ctx			Application context
 * @param	start		Starting point of the line
 * @param	end			Ending point of the line
 * @param	color		Color of the line
 */
void	draw_line_img(t_app *ctx, t_point start, t_point end,
		unsigned int color)
{
	t_point	stat;
	t_point	inc;
	t_point	d;
	double	steps;
	int		i;

	d.x = end.x - start.x;
	d.y = end.y - start.y;
	steps = fmax(fabs(d.x), fabs(d.y));
	inc.x = d.x / steps;
	inc.y = d.y / steps;
	stat.x = start.x;
	stat.y = start.y;
	i = 0;
	while (i <= steps)
	{
		if (stat.x >= 0 && stat.x < ctx->map.width && stat.y >= 0
			&& stat.y < ctx->map.height)
			put_pixel_to_img(ctx->img, (int)round(stat.x), (int)round(stat.y),
				color);
		stat.x += inc.x;
		stat.y += inc.y;
		i++;
	}
}
