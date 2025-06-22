/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_texture.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:39:02 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/18 13:42:11 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This file contains mainly stuff for resolving paths.
*/

#include "cub3d.h"
#include "libft.h"
#include "texture.h"
#include "utils.h"
#include <stdlib.h>

/*
** Free array of resolved texture paths
*/
static bool	free_resolved_paths(char **paths)
{
	int	i;

	if (!paths)
		return (true);
	i = 0;
	while (i < 5)
	{
		if (paths[i])
			free(paths[i]);
		i++;
	}
	free(paths);
	return (true);
}

bool	load_game_textures(t_data *data)
{
	char	**resolved_paths;
	bool	success;

	if (!data || !data->texture_n || !data->texture_e || !data->texture_s
		|| !data->texture_w)
	{
		ft_printf(RED "Error\nMissing texture paths\n" RESET);
		return (true);
	}
	resolved_paths = resolve_texture_paths(data, data->map_file_path);
	if (!resolved_paths)
	{
		ft_printf(RED "Error\nFailed to resolve texture paths\n" RESET);
		return (true);
	}
	success = load_textures(&data->textures, data->mlx, resolved_paths);
	free_resolved_paths(resolved_paths);
	if (!success)
	{
		ft_printf(RED "Error\nFailed to load textures\n" RESET);
		return (true);
	}
	if (load_game_textures_bonus(data))
		return (true);
	return (false);
}
