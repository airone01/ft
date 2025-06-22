/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_draw2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 18:36:38 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/17 18:52:06 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw.h"

void	draw_ceiling(t_data *data, int x, int start_y, t_color ceil_color)
{
	int	y;

	y = -1;
	while (++y < start_y)
		my_mlx_pixel_put(&data->img, x, y, ceil_color);
}

void	draw_floor(t_data *data, int x, int end_y, t_color floor_color)
{
	int	y;

	y = end_y;
	while (++y < data->win_height)
		my_mlx_pixel_put(&data->img, x, y, floor_color);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, t_color color)
{
	char	*dst;

	if (!img || !img->addr)
		return ;
	if (x < 0 || y < 0 || x >= WIN_W || y >= WIN_H)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color.val;
}
