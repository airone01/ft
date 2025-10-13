/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_free.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/19 15:57:10 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/20 19:32:40 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "mlx.h"
#include "sprite_bonus.h"
#include <stdlib.h>

void	free_map(t_data *data)
{
	int	i;

	if (!data->map)
		return ;
	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
	data->map = NULL;
}

void	free_map_copy(char **map_copy, int height)
{
	int	i;

	if (!map_copy)
		return ;
	i = 0;
	while (i < height)
	{
		if (map_copy[i])
			free(map_copy[i]);
		i++;
	}
	free(map_copy);
}

static void	free_textures(t_data *data)
{
	if (data->textures.north.img)
		mlx_destroy_image(data->mlx, data->textures.north.img);
	if (data->textures.south.img)
		mlx_destroy_image(data->mlx, data->textures.south.img);
	if (data->textures.east.img)
		mlx_destroy_image(data->mlx, data->textures.east.img);
	if (data->textures.west.img)
		mlx_destroy_image(data->mlx, data->textures.west.img);
	if (data->textures.door.img)
		mlx_destroy_image(data->mlx, data->textures.door.img);
}

static void	free_paths(t_data *data)
{
	if (data->texture_n)
		free(data->texture_n);
	if (data->texture_s)
		free(data->texture_s);
	if (data->texture_e)
		free(data->texture_e);
	if (data->texture_w)
		free(data->texture_w);
	if (data->texture_door)
		free(data->texture_door);
	if (data->map_file_path)
		free(data->map_file_path);
	if (data->texture_sprite)
		free(data->texture_sprite);
}

void	*free_resources(t_data **data)
{
	t_data	*d;

	if (!data || !*data)
		return (NULL);
	d = *data;
	if (d->map)
		free_map(d);
	d->map = NULL;
	free_paths(d);
	free_textures(d);
	free_door_system(d);
	free_sprite_system(d);
	if (d->img.img)
		mlx_destroy_image(d->mlx, d->img.img);
	if (d->win)
		mlx_destroy_window(d->mlx, d->win);
	if (d->mlx)
		mlx_destroy_display(d->mlx);
	if (d->z_buffer)
		free(d->z_buffer);
	free(d->mlx);
	free(d);
	*data = NULL;
	return (NULL);
}
