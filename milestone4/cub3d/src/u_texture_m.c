/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_texture_m.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:28:48 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/18 14:29:05 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "texture.h"
#include "utils.h"

bool	load_game_textures_bonus(t_data *data)
{
	(void)data;
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
	return (resolved_paths);
}
