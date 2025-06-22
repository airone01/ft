/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_map_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximart <maximart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 09:01:38 by maximart          #+#    #+#             */
/*   Updated: 2025/06/18 12:15:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mem.h"
#include "parsing.h"
#include "utils.h"

static bool	find_player_position(t_data *data, int *start_x, int *start_y)
{
	int	x;
	int	y;

	y = 0;
	while (y < data->map_height && data->map[y])
	{
		x = 0;
		while (x < data->map_width && data->map[y][x])
		{
			if (data->map[y][x] == 'N' || data->map[y][x] == 'S'
				|| data->map[y][x] == 'E' || data->map[y][x] == 'W')
			{
				*start_x = x;
				*start_y = y;
				return (true);
			}
			x++;
		}
		y++;
	}
	return (false);
}

static bool	validate_map_flood_fill(t_data *data)
{
	char	**map_copy;
	int		start_x;
	int		start_y;
	bool	result;

	if (!find_player_position(data, &start_x, &start_y))
		return (true);
	map_copy = create_map_copy(data);
	if (!map_copy)
	{
		ft_printf(RED "Error\nMemory allocation failed for the map\n" RESET);
		return (true);
	}
	result = flood_fill_recursive(map_copy, start_x, start_y, data);
	free_map_copy(map_copy, data->map_height);
	if (result)
	{
		ft_printf(RED "Error\nPlayer is not enclosed by walls\n" RESET);
		return (true);
	}
	return (false);
}

static bool	check_invalid_characters(t_data *data)
{
	int		x;
	int		y;
	char	c;

	y = 0;
	while (y < data->map_height && data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			c = data->map[y][x];
			if (!ft_strchr(map_chars(), c))
			{
				data->error_detected = true;
				ft_printf(RED "Error\nInvalid '%c' in map\n" RESET, c);
				return (true);
			}
			x++;
		}
		y++;
	}
	return (false);
}

static bool	check_player_count(t_data *data)
{
	int		x;
	int		y;
	int		player_count;
	char	c;

	player_count = 0;
	y = 0;
	while (y < data->map_height && data->map[y])
	{
		x = 0;
		while (data->map[y][x])
		{
			c = data->map[y][x];
			if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
				player_count++;
			x++;
		}
		y++;
	}
	if (player_count != 1)
	{
		ft_printf(RED "Error\nMap must contain exactly one player\n" RESET);
		return (true);
	}
	return (false);
}

bool	check_map_validity(t_data *data)
{
	if (data->map_height <= 0 || data->map_width <= 0 || !data->map)
	{
		ft_printf(RED "Error\nInvalid map structure\n" RESET);
		return (true);
	}
	if (check_invalid_characters(data))
		return (true);
	if (check_player_count(data))
		return (true);
	if (validate_map_flood_fill(data))
		return (true);
	return (false);
}
