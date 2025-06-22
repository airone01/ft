/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_render.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 18:10:47 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/20 19:25:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw.h"
#include "libft.h"
#include "mlx.h"
#include "player.h"
#include "pproc.h"
#include "raycasting.h"
#include "sprite_bonus.h"

/*
** Rendering pipeline. Note: we memset the image to zero, idk if it's a good
** idea.
*/
void	render_frame(t_data *data)
{
	struct timeval	now;
	double			elapsed;

	gettimeofday(&now, NULL);
	elapsed = ((now.tv_sec - data->last_frame.tv_sec) + (now.tv_usec
				- data->last_frame.tv_usec) / 1000000.0);
	data->delta_time = elapsed;
	data->last_frame = now;
	data->player.move_speed = BASE_MOVE_SPEED * data->delta_time;
	data->player.rot_speed = BASE_ROT_SPEED * data->delta_time;
	if (data->player.move_speed > 0.2)
		data->player.move_speed = 0.2;
	if (data->player.rot_speed > 0.15)
		data->player.rot_speed = 0.15;
	move_player(data, &data->player, data->map);
	ft_memset(data->img.addr, 0, data->win_width * data->win_height
		* (data->img.bits_per_pixel / 8));
	grid_raycasting(data);
	render_sprites(data);
	handle_render_bonus_features(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.img, 0, 0);
	handle_render_extra_features(data);
}
