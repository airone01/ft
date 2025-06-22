/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_system_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:41:53 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/20 19:52:03 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "mlx.h"
#include "sprite_bonus.h"

bool	add_sprite(t_data *data, double x, double y)
{
	t_sprite	*sprite;

	if (data->sprite_sys.count >= data->sprite_sys.capacity)
		return (false);
	sprite = &data->sprite_sys.sprites[data->sprite_sys.count];
	sprite->x = x;
	sprite->y = y;
	sprite->active = true;
	sprite->distance = 0;
	sprite->scale = SPRITE_SCALE;
	if (!load_sprite_textures(data, sprite))
	{
		ft_printf(RED "Error\nFailed to load sprite textures\n" RESET);
		return (false);
	}
	data->sprite_sys.count++;
	return (true);
}

static void	scan_map_for_sprites(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < data->map_height)
	{
		x = -1;
		while (++x < data->map_width && data->map[y]
			&& x < (int)ft_strlen(data->map[y]))
		{
			if (data->map[y][x] == 'P')
			{
				add_sprite(data, x + 0.5, y + 0.5);
				data->map[y][x] = '0';
			}
		}
	}
}

void	init_sprite_system(t_data *data)
{
	data->sprite_sys.capacity = 100;
	data->sprite_sys.count = 0;
	data->sprite_sys.sprites = ft_calloc(data->sprite_sys.capacity,
			sizeof(t_sprite));
	data->sprite_sys.render_order = ft_calloc(data->sprite_sys.capacity,
			sizeof(int));
	if (!data->sprite_sys.sprites || !data->sprite_sys.render_order)
	{
		ft_printf(RED "Error\nFailed to allocate memory for sprite system\n"
			RESET);
		return ;
	}
	scan_map_for_sprites(data);
}

void	free_sprite_system(t_data *data)
{
	int	i;
	int	j;

	if (data->sprite_sys.sprites)
	{
		i = -1;
		while (++i < data->sprite_sys.count)
		{
			j = -1;
			while (++j < data->sprite_sys.sprites[i].animation.frame_count)
			{
				if (data->sprite_sys.sprites[i].animation.frames[j].img)
					mlx_destroy_image(data->mlx,
						data->sprite_sys.sprites[i].animation.frames[j].img);
			}
		}
		free(data->sprite_sys.sprites);
		data->sprite_sys.sprites = NULL;
	}
	if (data->sprite_sys.render_order)
		free(data->sprite_sys.render_order);
	data->sprite_sys.render_order = NULL;
	data->sprite_sys.count = 0;
	data->sprite_sys.capacity = 0;
}

void	update_sprite_animations(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->sprite_sys.count)
	{
		if (data->sprite_sys.sprites[i].active)
		{
			update_sprite_animation(&data->sprite_sys.sprites[i],
				data->delta_time);
		}
	}
}
