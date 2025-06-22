/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_draw_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximart <maximart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 12:34:56 by maximart          #+#    #+#             */
/*   Updated: 2025/06/18 13:43:01 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap_bonus.h"
#include <math.h>

static void	draw_single_fov_line(t_data *data, t_draw_params *params, int end_x,
		int end_y)
{
	params->x = params->player_screen[0];
	params->y = params->player_screen[1];
	params->width = end_x;
	params->height = end_y;
	draw_line(data, params);
}

void	draw_player_fov(t_data *data, t_draw_params *params)
{
	double	player_angle;
	int		fov_ends[4];

	params->color.val = MINIMAP_FOV_COLOR;
	player_angle = atan2(data->player.dir_y, data->player.dir_x);
	cast_fov_ray(data, params, player_angle - 0.6);
	fov_ends[0] = params->end_x;
	fov_ends[1] = params->end_y;
	cast_fov_ray(data, params, player_angle + 0.6);
	fov_ends[2] = params->end_x;
	fov_ends[3] = params->end_y;
	cast_fov_ray(data, params, player_angle);
	draw_single_fov_line(data, params, fov_ends[0], fov_ends[1]);
	draw_single_fov_line(data, params, fov_ends[2], fov_ends[3]);
}

void	draw_border_lines(t_data *data, t_draw_params *params)
{
	params->x = params->minimap_x;
	params->y = params->minimap_y;
	params->width = params->minimap_x + MINIMAP_SIZE;
	params->height = params->minimap_y;
	draw_line(data, params);
	params->y = params->minimap_y + MINIMAP_SIZE;
	params->height = params->minimap_y + MINIMAP_SIZE;
	draw_line(data, params);
	params->width = params->minimap_x;
	params->height = params->minimap_y + MINIMAP_SIZE;
	draw_line(data, params);
	params->x = params->minimap_x + MINIMAP_SIZE;
	params->width = params->minimap_x + MINIMAP_SIZE;
	params->height = params->minimap_y + MINIMAP_SIZE;
	draw_line(data, params);
}
