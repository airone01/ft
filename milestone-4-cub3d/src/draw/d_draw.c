/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   d_draw.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:31:43 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/18 13:37:59 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "door_bonus.h"
#include "draw.h"
#include "libft.h"
#include "texture.h"

static void	draw_line_pixels(t_data *data, t_ray *ray, t_texture *texture,
		int x)
{
	double	step;
	double	tex_pos;
	t_color	color;
	int		y;
	int		tex_y;

	step = 1.0 * texture->height / ray->line_height;
	tex_pos = (ray->draw_start - data->win_height / 2 + ray->line_height / 2)
		* step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		color = get_pixel_color(texture, ray->tex_x, tex_y);
		my_mlx_pixel_put(&data->img, x, y, color);
		y++;
	}
}

static void	draw_textured_line_init(t_ray *ray, struct s_double_int s,
		t_texture *texture, t_data *data)
{
	double	wall_x;

	wall_x = calculate_wall_hit(data, ray);
	ray->tex_x = calculate_texture_x(wall_x, texture, ray);
	if (ray->side == SIDE_EAST_WEST)
	{
		*s.x = (int)ray->vertical_x;
		*s.y = (int)ray->vertical_y;
	}
	else
	{
		*s.x = (int)ray->horizontal_x;
		*s.y = (int)ray->horizontal_y;
	}
}

void	draw_textured_line(t_data *data, t_ray *ray, int x)
{
	t_texture	*texture;
	t_door		*door;
	int			map_x;
	int			map_y;
	int			door_offset;

	texture = get_wall_texture(data, &data->textures, ray);
	draw_textured_line_init(ray, (struct s_double_int){&map_x, &map_y}, texture,
		data);
	if (map_y >= 0 && map_y < data->map_height && map_x >= 0
		&& map_x < data->map_width && data->map[map_y]
		&& map_x < (int)ft_strlen(data->map[map_y])
		&& data->map[map_y][map_x] == 'D')
	{
		door = get_door_at(data, map_x, map_y);
		if (door)
		{
			door_offset = (int)(door->prog * ray->line_height);
			ray->draw_start += door_offset;
			if (ray->draw_start > ray->draw_end)
				ray->draw_start = ray->draw_end;
		}
	}
	draw_line_pixels(data, ray, texture, x);
}
