/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   j_render_b.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 12:41:05 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/20 19:53:32 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "draw.h"
#include "sprite_bonus.h"
#include "texture.h"
#include <stdlib.h>

static void	calculate_sprite_transform(t_data *data, t_sprite *sprite,
		t_sprite_render *render)
{
	render->sprite_x = sprite->x - data->player.pos_x;
	render->sprite_y = data->player.pos_y - sprite->y;
	render->inv_det = 1.0 / (data->player.plane_x * data->player.dir_y
			- data->player.dir_x * data->player.plane_y);
	render->transform_x = render->inv_det * (data->player.dir_y
			* render->sprite_x - data->player.dir_x * render->sprite_y);
	render->transform_y = render->inv_det * (-data->player.plane_y
			* render->sprite_x + data->player.plane_x * render->sprite_y);
	render->sprite_screen_x = (int)((data->win_width / 2) * (1
				- render->transform_x / render->transform_y));
}

static void	calculate_sprite_dimensions(t_data *data, t_sprite *sprite,
		t_sprite_render *render)
{
	int	full_scale_height;
	int	full_scale_center_y;
	int	full_scale_bottom;

	full_scale_height = abs((int)(data->win_height / render->transform_y));
	render->sprite_height = full_scale_height * sprite->scale;
	full_scale_center_y = data->win_height / 2;
	full_scale_bottom = full_scale_center_y + (full_scale_height / 2);
	render->draw_end_y = full_scale_bottom;
	render->draw_start_y = render->draw_end_y - render->sprite_height;
	if (render->draw_start_y < 0)
		render->draw_start_y = 0;
	if (render->draw_end_y >= data->win_height)
		render->draw_end_y = data->win_height - 1;
	render->sprite_width = abs((int)(data->win_height / render->transform_y))
		* sprite->scale;
	render->draw_start_x = -render->sprite_width / 2 + render->sprite_screen_x;
	if (render->draw_start_x < 0)
		render->draw_start_x = 0;
	render->draw_end_x = render->sprite_width / 2 + render->sprite_screen_x;
	if (render->draw_end_x >= data->win_width)
		render->draw_end_x = data->win_width - 1;
}

/*
** Note: this is now aware of the z-buffer info given by grid_raycasting
*/
static void	draw_sprite_column(t_data *data, t_sprite_render *render,
		t_texture *texture, int stripe)
{
	int		y;
	int		tex_x;
	int		tex_y;
	t_color	color;

	tex_x = (int)(256 * (stripe - (-render->sprite_width / 2
					+ render->sprite_screen_x)) * texture->width
			/ render->sprite_width) / 256;
	if (render->transform_y > 0 && stripe >= 0 && stripe < data->win_width)
	{
		if (render->transform_y < data->z_buffer[stripe])
		{
			y = render->draw_start_y - 1;
			while (++y < render->draw_end_y)
			{
				tex_y = ((y - render->draw_start_y) * texture->height)
					/ render->sprite_height;
				color = get_pixel_color(texture, tex_x, tex_y);
				if ((color.val & 0x00FFFFFF) != 0x00FF00FF
					&& (color.val & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(&data->img, stripe, y, color);
			}
		}
	}
}

static void	render_single_sprite(t_data *data, t_sprite *sprite)
{
	t_sprite_render	render;
	t_texture		*texture;
	int				stripe;

	if (!is_sprite_visible(data, sprite))
		return ;
	texture = get_sprite_texture(sprite);
	if (!texture)
		return ;
	calculate_sprite_transform(data, sprite, &render);
	calculate_sprite_dimensions(data, sprite, &render);
	stripe = render.draw_start_x - 1;
	while (++stripe < render.draw_end_x)
		draw_sprite_column(data, &render, texture, stripe);
}

void	render_sprites(t_data *data)
{
	int	i;
	int	sprite_index;

	sort_sprites_by_distance(data);
	i = -1;
	while (++i < data->sprite_sys.count)
	{
		sprite_index = data->sprite_sys.render_order[i];
		if (data->sprite_sys.sprites[sprite_index].active)
			render_single_sprite(data, &data->sprite_sys.sprites[sprite_index]);
	}
}
