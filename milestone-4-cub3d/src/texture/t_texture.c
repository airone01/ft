/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_texture.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:20:52 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/16 18:05:00 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include "texture.h"

bool		load_bonus_textures(t_data *data, char *door_path);
t_texture	*get_wall_texture_bonus(t_data *data, t_textures *textures,
				t_ray *ray);

static bool	load_textures_ns(t_textures *textures, void *mlx_ptr,
		char *north_path, char *south_path)
{
	textures->north.img = mlx_xpm_file_to_image(mlx_ptr, north_path,
			&textures->north.width, &textures->north.height);
	if (!textures->north.img)
		return (false);
	textures->north.addr = mlx_get_data_addr(textures->north.img,
			&textures->north.bits_per_pixel, &textures->north.line_length,
			&textures->north.endian);
	textures->south.img = mlx_xpm_file_to_image(mlx_ptr, south_path,
			&textures->south.width, &textures->south.height);
	if (!textures->south.img)
		return (false);
	textures->south.addr = mlx_get_data_addr(textures->south.img,
			&textures->south.bits_per_pixel, &textures->south.line_length,
			&textures->south.endian);
	return (true);
}

static bool	load_textures_ew(t_textures *textures, void *mlx_ptr,
		char *east_path, char *west_path)
{
	textures->east.img = mlx_xpm_file_to_image(mlx_ptr, east_path,
			&textures->east.width, &textures->east.height);
	if (!textures->east.img)
		return (false);
	textures->east.addr = mlx_get_data_addr(textures->east.img,
			&textures->east.bits_per_pixel, &textures->east.line_length,
			&textures->east.endian);
	textures->west.img = mlx_xpm_file_to_image(mlx_ptr, west_path,
			&textures->west.width, &textures->west.height);
	if (!textures->west.img)
		return (false);
	textures->west.addr = mlx_get_data_addr(textures->west.img,
			&textures->west.bits_per_pixel, &textures->west.line_length,
			&textures->west.endian);
	return (true);
}

/*
** Values in `paths` are stored in the crescent order of azimuth (or clockwise
** hortizontal angle), meaing N, E, S, W.
** See the function prototype in the header file.
*/
bool	load_textures(t_textures *textures, void *mlx_ptr, char *paths[4])
{
	if (!load_textures_ns(textures, mlx_ptr, paths[0], paths[2]))
		return (false);
	if (!load_textures_ew(textures, mlx_ptr, paths[1], paths[3]))
		return (false);
	return (true);
}

t_color	get_pixel_color(t_texture *texture, int x, int y)
{
	char	*pixel;
	t_color	black;

	if (!texture || !texture->addr)
	{
		black.val = 0x000000;
		return (black);
	}
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
	{
		black.val = 0x000000;
		return (black);
	}
	pixel = texture->addr + (y * texture->line_length + x
			* (texture->bits_per_pixel / 8));
	return (*(t_color *)pixel);
}

t_texture	*get_wall_texture(t_data *data, t_textures *textures, t_ray *ray)
{
	t_texture	*txt;

	txt = get_wall_texture_bonus(data, textures, ray);
	if (txt)
		return (txt);
	if (ray->side == SIDE_NORTH_SHOUTH)
	{
		if (ray->ray_dir_y > 0)
			return (&textures->north);
		else
			return (&textures->south);
	}
	else
	{
		if (ray->ray_dir_x < 0)
			return (&textures->west);
		else
			return (&textures->east);
	}
}
