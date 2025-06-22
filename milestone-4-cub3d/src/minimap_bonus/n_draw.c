/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   n_draw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maximart <maximart@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/27 18:37:19 by maximart          #+#    #+#             */
/*   Updated: 2025/06/18 13:42:47 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "minimap_bonus.h"
#include <stdlib.h>

void	clamp_rect_bounds(t_data *data, t_draw_params *params)
{
	if (params->x + params->width > data->win_width)
		params->width = data->win_width - params->x;
	if (params->y + params->height > data->win_height)
		params->height = data->win_height - params->y;
}

static void	init_line_params(t_draw_params *params, int *dx, int *dy, int *step)
{
	*dx = abs(params->width - params->x);
	*dy = abs(params->height - params->y);
	if (params->x > params->width)
		step[0] = 1;
	else
		step[0] = -1;
	if (params->y > params->height)
		step[1] = 1;
	else
		step[1] = -1;
	params->start_x = *dx - *dy;
}

static void	draw_line_pixels(t_data *data, t_draw_params *params, int dx,
		int dy)
{
	int	err2;
	int	step_x;
	int	step_y;

	init_steps(params, &step_x, &step_y);
	while (1)
	{
		if (is_pixel_valid(data, params->x, params->y))
			my_mlx_pixel_put(&data->img, params->x, params->y, params->color);
		if (params->x == params->width && params->y == params->height)
			break ;
		err2 = 2 * params->start_x;
		if (err2 > -dy)
		{
			params->start_x -= dy;
			params->x += step_x;
		}
		if (err2 < dx)
		{
			params->start_x += dx;
			params->y += step_y;
		}
	}
}

void	draw_line(t_data *data, t_draw_params *params)
{
	int	dx;
	int	dy;
	int	step[2];

	init_line_params(params, &dx, &dy, step);
	draw_line_pixels(data, params, dx, dy);
}

void	draw_minimap_border(t_data *data, t_draw_params *params)
{
	params->color.val = MINIMAP_BORDER_COLOR;
	draw_border_lines(data, params);
}
