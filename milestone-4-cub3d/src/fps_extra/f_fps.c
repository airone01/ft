/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_fps.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:12:34 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/18 14:51:29 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "mlx.h"
#include <stdio.h>
#include <sys/time.h>

/*
** Calculate time difference between two timeval structs in seconds
*/
static double	get_time_diff(struct timeval *start, struct timeval *end)
{
	return ((end->tv_sec - start->tv_sec) + (end->tv_usec - start->tv_usec)
		/ 1000000.0);
}

void	update_fps_counter(t_data *data)
{
	double	elapsed;

	gettimeofday(&data->current_frame, NULL);
	elapsed = get_time_diff(&data->last_frame, &data->current_frame);
	data->fps_timer += elapsed;
	data->frame_count++;
	if (data->fps_timer >= 0.5)
	{
		data->fps = data->frame_count / data->fps_timer;
		data->frame_count = 0;
		data->fps_timer = 0.0;
	}
}

void	display_fps(t_data *data)
{
	char	fps_text[32];
	t_color	c;
	int		x;
	int		y;

	c.val = 0x000000;
	snprintf(fps_text, sizeof(fps_text), "FPS: %.1f", data->fps);
	y = 4;
	while (++y < 5 + FPS_COUNTER_TEXT_HEIGHT)
	{
		x = 4;
		while (++x < 5 + FPS_COUNTER_TEXT_WIDTH)
		{
			if (x < data->win_width && y < data->win_height)
				my_mlx_pixel_put(&data->img, x, y, c);
		}
	}
	mlx_string_put(data->mlx, data->win, 10, 20, 0xFFFFFF, fps_text);
}
