/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_grid.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximart <maximart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:37:40 by maximart          #+#    #+#             */
/*   Updated: 2025/05/27 18:37:40 by maximart         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "minimap_bonus.h"

static bool	check_grid_bounds(t_draw_params *params)
{
	if (params->x + params->cell_size > params->minimap_x
		&& params->x < params->minimap_x + MINIMAP_SIZE && params->y
		+ params->cell_size > params->minimap_y && params->y < params->minimap_y
		+ MINIMAP_SIZE)
		return (true);
	return (false);
}

static void	set_grid_draw_bounds(t_draw_params *params)
{
	if (params->x < params->minimap_x)
		params->x = params->minimap_x;
	if (params->y < params->minimap_y)
		params->y = params->minimap_y;
	params->width = params->cell_size;
	params->height = params->cell_size;
	if (params->x + params->width > params->minimap_x + MINIMAP_SIZE)
		params->width = params->minimap_x + MINIMAP_SIZE - params->x;
	if (params->y + params->height > params->minimap_y + MINIMAP_SIZE)
		params->height = params->minimap_y + MINIMAP_SIZE - params->y;
}

static void	draw_grid_cell(t_data *data, t_draw_params *params, char cell)
{
	if (cell == '1')
	{
		params->color.val = MINIMAP_WALL_COLOR;
		draw_filled_rect(data, params);
	}
	else if (cell == '0')
	{
		params->color.val = data->floor_color.val;
		draw_filled_rect(data, params);
	}
}

static void	process_grid_cell(t_data *data, t_draw_params *params, int map_x,
		int map_y)
{
	params->x = params->minimap_x + (map_x * params->cell_size)
		- params->start_x;
	params->y = params->minimap_y + (map_y * params->cell_size)
		- params->start_y;
	if (check_grid_bounds(params))
	{
		set_grid_draw_bounds(params);
		if (params->width > 0 && params->height > 0)
			draw_grid_cell(data, params, data->map[map_y][map_x]);
	}
}

void	draw_minimap_grid(t_data *data, t_draw_params *params)
{
	int	map_x;
	int	map_y;

	map_y = 0;
	while (map_y < data->map_height)
	{
		map_x = 0;
		while (map_x < data->map_width && data->map[map_y][map_x])
		{
			process_grid_cell(data, params, map_x, map_y);
			map_x++;
		}
		map_y++;
	}
}
