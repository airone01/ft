/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_animation_b2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 19:45:18 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/20 19:50:34 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include <stdio.h>

void	init_sprite_animation(t_sprite *sprite)
{
	sprite->animation.frame_count = 0;
	sprite->animation.frame_duration = 0.5f;
	sprite->animation.current_time = 0.0f;
	sprite->animation.current_frame = 0;
	sprite->animation.loop = true;
}

char	*create_frame_path(char *base_path, int frame_num)
{
	char	frame_suffix[10];
	char	*frame_path;

	snprintf(frame_suffix, sizeof(frame_suffix), "_%02d.xpm", frame_num);
	frame_path = ft_strjoin(base_path, frame_suffix);
	return (frame_path);
}

bool	load_single_frame(t_data *data, t_sprite *sprite, char *resolved_path,
							int frame_idx)
{
	sprite->animation.frames[frame_idx].img = mlx_xpm_file_to_image(data->mlx,
			resolved_path, &sprite->animation.frames[frame_idx].width,
			&sprite->animation.frames[frame_idx].height);
	if (!sprite->animation.frames[frame_idx].img)
		return (false);
	sprite->animation.frames[frame_idx].addr = mlx_get_data_addr(
			sprite->animation.frames[frame_idx].img,
			&sprite->animation.frames[frame_idx].bits_per_pixel,
			&sprite->animation.frames[frame_idx].line_length,
			&sprite->animation.frames[frame_idx].endian);
	return (true);
}
