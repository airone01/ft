/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_map_op.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/01 14:38:58 by elagouch          #+#    #+#             */
/*   Updated: 2024/10/02 19:25:26 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"
#include <stdio.h>

/*
 * Frees a map struct.
 *
 * @param	map	pointer to a map struct
 */
void	bsq_smap_free(t_map *map)
{
	if (map != NULL)
		bsq_map_free(map->map, map->coords);
	free(map);
}

/*
 * Frees a matrix of tiles.
 *
 * @param	map		matrix of tiles
 * @param	coords	lengths of x and y of the map
 */
void	bsq_map_free(t_tile **map, t_coords coords)
{
	int	i;

	i = 0;
	while (i < coords.y)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

/*
 * Allocates and initializes a map
 *
 * @param	coords	lengths of x and y of the map
 *
 * @return	allocated map
 */
t_tile	**bsq_map_init(t_coords coords)
{
	t_tile	**map;
	int		i;
	int		j;

	map = (t_tile **)malloc(coords.y * sizeof(t_tile *));
	i = 0;
	while (i < coords.y)
	{
		map[i] = (t_tile *)malloc(coords.x * sizeof(t_tile));
		j = 0;
		while (j < coords.x)
		{
			map[i][j] = epty;
			j++;
		}
		i++;
	}
	return (map);
}

/*
 * Counts the number of lines before NUL in an array of strings.
 *
 * @param	strs	array of strings
 *
 * @returns	number of lines
 */
int	bsq_matrix_count(char **strs)
{
	while (!strs || !*strs)
		return (0);
	return (bsq_matrix_count(strs + 1) + 1);
}
