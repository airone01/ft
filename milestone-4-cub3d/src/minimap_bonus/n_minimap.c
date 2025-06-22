/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_minimap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximart <maximart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:35:43 by maximart          #+#    #+#             */
/*   Updated: 2025/05/27 18:35:44 by maximart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "minimap_bonus.h"

static void	init_draw_params(t_draw_params *params, t_data *data)
{
	params->minimap_x = MINIMAP_MARGIN;
	params->minimap_y = data->win_height - MINIMAP_SIZE - MINIMAP_MARGIN;
	params->cell_size = MINIMAP_SIZE / MINIMAP_SCALE;
	params->center_x = (int)(data->player.pos_x * params->cell_size);
	params->center_y = (int)(data->player.pos_y * params->cell_size);
	params->start_x = params->center_x - MINIMAP_SIZE / 2;
	params->start_y = params->center_y - MINIMAP_SIZE / 2;
}

static void	draw_minimap_background(t_data *data, t_draw_params *params)
{
	params->color.val = 0x150000;
	params->x = params->minimap_x;
	params->y = params->minimap_y;
	params->width = MINIMAP_SIZE;
	params->height = MINIMAP_SIZE;
	draw_filled_rect(data, params);
}

static void	draw_minimap_elements(t_data *data, t_draw_params *params)
{
	draw_minimap_grid(data, params);
	draw_minimap_player(data, params);
	draw_minimap_border(data, params);
}

void	draw_minimap(t_data *data)
{
	t_draw_params	params;

	init_draw_params(&params, data);
	draw_minimap_background(data, &params);
	draw_minimap_elements(data, &params);
}

void	draw_filled_rect(t_data *data, t_draw_params *params)
{
	int	i;
	int	j;

	if (params->x >= data->win_width || params->y >= data->win_height
		|| params->x + params->width <= 0 || params->y + params->height <= 0)
		return ;
	if (params->width <= 0 || params->height <= 0)
		return ;
	if (params->x < 0)
		params->x = 0;
	if (params->y < 0)
		params->y = 0;
	clamp_rect_bounds(data, params);
	i = params->y;
	while (i < params->y + params->height)
	{
		j = params->x;
		while (j < params->x + params->width)
		{
			my_mlx_pixel_put(&data->img, j, i, params->color);
			j++;
		}
		i++;
	}
}
