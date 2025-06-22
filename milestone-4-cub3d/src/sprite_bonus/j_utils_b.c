/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_utils_b.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:40:35 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/20 19:53:50 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "sprite_bonus.h"
#include <stdio.h>
#include <unistd.h>

t_texture	*get_sprite_texture(t_sprite *sprite)
{
	if (!sprite || !sprite->active)
	{
		printf("Sprite is NULL or inactive\n");
		return (NULL);
	}
	if (sprite->animation.current_frame >= sprite->animation.frame_count)
	{
		printf("Frame out of bounds: current=%d, count=%d\n",
			sprite->animation.current_frame, sprite->animation.frame_count);
		return (NULL);
	}
	return (&sprite->animation.frames[sprite->animation.current_frame]);
}

/*
** I'm too lazy to actually implement that
*/
bool	is_sprite_visible(t_data *data, t_sprite *sprite)
{
	(void)data;
	(void)sprite;
	return (true);
}
