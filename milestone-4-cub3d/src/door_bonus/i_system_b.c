/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_system_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:00:20 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/20 19:39:12 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static void	init_door_system_loop(t_data *data, int x, int y)
{
	if (data->map[y][x] == 'D')
	{
		if (data->door_sys.count < data->door_sys.capacity)
		{
			data->door_sys.doors[data->door_sys.count].x = x;
			data->door_sys.doors[data->door_sys.count].y = y;
			data->door_sys.doors[data->door_sys.count].open = false;
			data->door_sys.doors[data->door_sys.count].opening = false;
			data->door_sys.doors[data->door_sys.count].closing = false;
			data->door_sys.doors[data->door_sys.count].prog = 0.0f;
			data->door_sys.count++;
		}
	}
}

void	init_door_system(t_data *data)
{
	int	x;
	int	y;

	data->door_sys.capacity = 100;
	data->door_sys.animation_speed = 3.0f;
	data->door_sys.doors = ft_calloc(data->door_sys.capacity, sizeof(t_door));
	if (!data->door_sys.doors)
	{
		ft_printf(RED "Error\nFailed to allocate memory for door system\n"
			RESET);
		return ;
	}
	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width && data->map[y]
			&& x < (int)ft_strlen(data->map[y]))
			init_door_system_loop(data, x, y);
	}
}

static void	update_door_animations_else(t_data *data, t_door *door)
{
	door->prog -= data->door_sys.animation_speed * data->delta_time;
	if (door->prog <= 0.0f)
	{
		door->prog = 0.0f;
		door->closing = false;
		door->open = false;
	}
}

void	update_door_animations(t_data *data)
{
	int		i;
	t_door	*door;

	i = -1;
	while (++i < data->door_sys.count)
	{
		door = &data->door_sys.doors[i];
		if (door->opening)
		{
			door->prog += data->door_sys.animation_speed * data->delta_time;
			if (door->prog >= 1.0f)
			{
				door->prog = 1.0f;
				door->opening = false;
				door->open = true;
			}
		}
		else if (door->closing)
			update_door_animations_else(data, door);
	}
}

void	free_door_system(t_data *data)
{
	if (data->door_sys.doors)
	{
		free(data->door_sys.doors);
		data->door_sys.doors = NULL;
	}
	data->door_sys.count = 0;
	data->door_sys.capacity = 0;
}
