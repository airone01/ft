/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_animation_b.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:40:20 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/20 19:51:12 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "sprite_bonus.h"
#include "utils.h"
#include <stdlib.h>

void	init_sprite_animation(t_sprite *sprite);
char	*create_frame_path(char *base_path, int frame_num);
bool	load_single_frame(t_data *data, t_sprite *sprite, char *resolved_path,
			int frame_idx);

static int	load_animated_frames(t_data *data, t_sprite *sprite,
								char *base_path)
{
	int		frame;
	int		valid_frames;
	char	*frame_path;
	char	*resolved_path;

	frame = 1;
	valid_frames = 0;
	while (frame <= MAX_SPRITE_FRAMES && valid_frames < MAX_SPRITE_FRAMES)
	{
		frame_path = create_frame_path(base_path, frame);
		if (!frame_path)
			break ;
		resolved_path = resolve_path(data->map_file_path, frame_path);
		free(frame_path);
		if (!resolved_path)
		{
			frame++;
			continue ;
		}
		if (load_single_frame(data, sprite, resolved_path, valid_frames))
			valid_frames++;
		free(resolved_path);
		frame++;
	}
	return (valid_frames);
}

static bool	load_fallback_frame(t_data *data, t_sprite *sprite)
{
	char	*resolved_path;
	bool	success;

	resolved_path = resolve_path(data->map_file_path, data->texture_sprite);
	if (!resolved_path)
		return (false);
	success = load_single_frame(data, sprite, resolved_path, 0);
	free(resolved_path);
	if (success)
		sprite->animation.frame_count = 1;
	return (success);
}

bool	load_sprite_textures(t_data *data, t_sprite *sprite)
{
	char	*base_path;
	char	*extension;
	int		valid_frames;

	if (!data->texture_sprite)
		return (false);
	init_sprite_animation(sprite);
	base_path = ft_strdup(data->texture_sprite);
	extension = ft_strrchr(base_path, '.');
	if (extension)
		*extension = '\0';
	valid_frames = load_animated_frames(data, sprite, base_path);
	sprite->animation.frame_count = valid_frames;
	free(base_path);
	if (sprite->animation.frame_count == 0)
		return (load_fallback_frame(data, sprite));
	return (true);
}

void	update_sprite_animation(t_sprite *sprite, double delta_time)
{
	if (sprite->animation.frame_count <= 1)
		return ;
	sprite->animation.current_time += delta_time;
	if (sprite->animation.current_time
		>= sprite->animation.frame_duration)
	{
		sprite->animation.current_time = 0.0f;
		sprite->animation.current_frame++;
		if (sprite->animation.current_frame
			>= sprite->animation.frame_count)
		{
			if (sprite->animation.loop)
				sprite->animation.current_frame = 0;
			else
				sprite->animation.current_frame
					= sprite->animation.frame_count - 1;
		}
	}
}
