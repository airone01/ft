/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_player.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximart <maximart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:38:03 by maximart          #+#    #+#             */
/*   Updated: 2025/06/18 13:43:16 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minimap_bonus.h"

static bool	is_wall_at_map_pos(t_data *data, int map_x, int map_y)
{
	if (map_x < 0 || map_y < 0 || map_y >= data->map_height)
		return (true);
	if (map_x >= data->map_width || !data->map[map_y])
		return (true);
	if (map_x >= (int)ft_strlen(data->map[map_y]))
		return (true);
	return (data->map[map_y][map_x] == '1');
}

static void	clamp_ray_endpoint(t_draw_params *params, int screen_x,
		int screen_y)
{
	if (screen_x < params->minimap_x)
		params->end_x = params->minimap_x;
	else if (screen_x >= params->minimap_x + MINIMAP_SIZE)
		params->end_x = params->minimap_x + MINIMAP_SIZE - 1;
	else
		params->end_x = screen_x;
	if (screen_y < params->minimap_y)
		params->end_y = params->minimap_y;
	else if (screen_y >= params->minimap_y + MINIMAP_SIZE)
		params->end_y = params->minimap_y + MINIMAP_SIZE - 1;
	else
		params->end_y = screen_y;
}

static void	map_to_screen(t_draw_params *params, double *ray_pos,
		int *screen_pos)
{
	screen_pos[0] = params->minimap_x + (int)(ray_pos[0] * params->cell_size)
		- params->start_x;
	screen_pos[1] = params->minimap_y + (int)(ray_pos[1] * params->cell_size)
		- params->start_y;
}

void	cast_fov_ray(t_data *data, t_draw_params *params, double angle)
{
	double	ray_pos[2];
	double	ray_dir[2];
	int		steps;
	int		screen_pos[2];

	init_ray_pos(data, angle, ray_pos, ray_dir);
	steps = 0;
	while (steps < MINIMAP_FOV_LENGTH)
	{
		ray_pos[0] += ray_dir[0];
		ray_pos[1] += ray_dir[1];
		steps++;
		if (is_wall_at_map_pos(data, (int)ray_pos[0], (int)ray_pos[1]))
		{
			ray_pos[0] -= ray_dir[0];
			ray_pos[1] -= ray_dir[1];
			break ;
		}
		map_to_screen(params, ray_pos, screen_pos);
		if (check_fov_bounds(params, screen_pos[0], screen_pos[1]))
			break ;
	}
	map_to_screen(params, ray_pos, screen_pos);
	clamp_ray_endpoint(params, screen_pos[0], screen_pos[1]);
}

void	draw_minimap_player(t_data *data, t_draw_params *params)
{
	params->player_screen[0] = params->minimap_x + MINIMAP_SIZE / 2;
	params->player_screen[1] = params->minimap_y + MINIMAP_SIZE / 2;
	params->color.val = MINIMAP_PLAYER_COLOR;
	params->x = params->player_screen[0] - MINIMAP_PLAYER_SIZE / 2;
	params->y = params->player_screen[1] - MINIMAP_PLAYER_SIZE / 2;
	if (is_player_in_bounds(params))
	{
		params->width = MINIMAP_PLAYER_SIZE;
		params->height = MINIMAP_PLAYER_SIZE;
		draw_filled_rect(data, params);
	}
	draw_player_fov(data, params);
}
