/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_texture_b.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 14:46:09 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/18 14:19:25 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "texture.h"
#include "utils.h"

bool	load_game_textures_bonus(t_data *data)
{
	char	*door_resolved_path;
	bool	door_success;

	if (data->texture_door)
	{
		door_resolved_path = resolve_path(data->map_file_path,
				data->texture_door);
		if (!door_resolved_path)
		{
			ft_printf(RED "Error\nFailed to resolve door texture path\n" RESET);
			return (true);
		}
		door_success = load_bonus_textures(data, door_resolved_path);
		free(door_resolved_path);
		if (door_success)
		{
			ft_printf(RED "Error\nFailed to load door texture\n" RESET);
			return (true);
		}
	}
	return (false);
}

char	**resolve_texture_paths(t_data *data, const char *map_path)
{
	char	**resolved_paths;

	resolved_paths = ft_calloc(6, sizeof(char *));
	if (!resolved_paths)
		return (NULL);
	resolved_paths[0] = resolve_path(map_path, data->texture_n);
	resolved_paths[1] = resolve_path(map_path, data->texture_e);
	resolved_paths[2] = resolve_path(map_path, data->texture_s);
	resolved_paths[3] = resolve_path(map_path, data->texture_w);
	resolved_paths[4] = resolve_path(map_path, data->texture_door);
	return (resolved_paths);
}
