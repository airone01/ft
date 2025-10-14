/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximart <maximart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:38:26 by maximart          #+#    #+#             */
/*   Updated: 2025/06/18 13:43:28 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minimap_bonus.h"
#include <math.h>

bool	check_fov_bounds(t_draw_params *params, int screen_x, int screen_y)
{
	if (screen_x < params->minimap_x || screen_x >= params->minimap_x
		+ MINIMAP_SIZE || screen_y < params->minimap_y
		|| screen_y >= params->minimap_y + MINIMAP_SIZE)
		return (true);
	return (false);
}

bool	is_player_in_bounds(t_draw_params *params)
{
	if (params->x >= params->minimap_x && params->y >= params->minimap_y
		&& params->x + MINIMAP_PLAYER_SIZE <= params->minimap_x + MINIMAP_SIZE
		&& params->y + MINIMAP_PLAYER_SIZE <= params->minimap_y + MINIMAP_SIZE)
		return (true);
	return (false);
}

int	is_pixel_valid(t_data *data, int x, int y)
{
	if (x >= 0 && y >= 0 && x < data->win_width && y < data->win_height)
		return (1);
	return (0);
}

void	init_steps(t_draw_params *params, int *step_x, int *step_y)
{
	if (params->width > params->x)
		*step_x = 1;
	else
		*step_x = -1;
	if (params->height > params->y)
		*step_y = 1;
	else
		*step_y = -1;
}

void	init_ray_pos(t_data *data, double angle, double *ray_pos,
		double *ray_dir)
{
	ray_pos[0] = data->player.pos_x;
	ray_pos[1] = data->player.pos_y;
	ray_dir[0] = cos(-angle) * 0.02;
	ray_dir[1] = sin(-angle) * 0.02;
}
