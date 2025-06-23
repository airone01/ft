/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   l_init.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 18:49:24 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/21 16:54:34 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Originally this file was `player.c`, but it was split into `player_move.c`
** and `player_init.c` because both functions are too large.
*/

#include "cub3d.h"

/*
** This function will find the player character in the map by looping through
** each character, and then save their position, direction and manually set the
** corresponding tile to an empty tile.
*/
static char	find_and_place_player(t_data *data)
{
	int		x;
	int		y;
	char	dir;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (data->map[y][++x] && x < data->map_width)
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'E' || data->map[y][x] == 'W')
			{
				data->player.pos_x = x + 0.5;
				data->player.pos_y = y + 0.5;
				dir = data->map[y][x];
				data->map[y][x] = '0';
				x = data->map_width;
				y = data->map_height;
				return (dir);
			}
		}
	}
	return ('\0');
}

static void	set_initial_camera_plane(t_data *data, char dir)
{
	if (dir == 'N')
	{
		data->player.dir_x = 0;
		data->player.dir_y = 1;
	}
	else if (dir == 'S')
	{
		data->player.dir_x = 0;
		data->player.dir_y = -1;
	}
	else if (dir == 'E')
	{
		data->player.dir_x = 1;
		data->player.dir_y = 0;
	}
	else if (dir == 'W')
	{
		data->player.dir_x = -1;
		data->player.dir_y = 0;
	}
	data->player.plane_x = -data->player.dir_y * 0.66;
	data->player.plane_y = data->player.dir_x * 0.66;
}

static void	set_initial_player_data(t_data *data)
{
	data->player.move_speed = 0.05;
	data->player.rot_speed = 0.03;
	data->player.move_forward = 0;
	data->player.move_backward = 0;
	data->player.move_left = 0;
	data->player.move_right = 0;
	data->player.rotate_left = 0;
	data->player.rotate_right = 0;
	data->player.cam_height = data->win_height / 2.0;
}

void	init_player(t_data *data)
{
	char	dir;

	dir = find_and_place_player(data);
	set_initial_camera_plane(data, dir);
	set_initial_player_data(data);
}
