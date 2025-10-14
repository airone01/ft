/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_system_b2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 13:25:26 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/18 13:42:36 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <unistd.h>

t_door	*get_door_at(t_data *data, int x, int y)
{
	int	i;

	i = -1;
	while (++i < data->door_sys.count)
	{
		if (data->door_sys.doors[i].x == x && data->door_sys.doors[i].y == y)
			return (&data->door_sys.doors[i]);
	}
	return (NULL);
}

void	toggle_door(t_data *data, int x, int y)
{
	t_door	*door;

	door = get_door_at(data, x, y);
	if (!door)
		return ;
	if (door->open || door->opening)
	{
		door->open = false;
		door->opening = false;
		door->closing = true;
	}
	else if (!door->open || door->closing)
	{
		door->open = false;
		door->closing = false;
		door->opening = true;
	}
}

bool	is_door_passable(t_data *data, int x, int y)
{
	t_door	*door;

	door = get_door_at(data, x, y);
	if (!door)
		return (false);
	return (door->prog > 0.7f);
}
