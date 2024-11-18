/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_map_read.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:43:52 by elagouch          #+#    #+#             */
/*   Updated: 2024/10/02 19:40:40 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"

/*
 * Checks if the map is correct by calculating
 * the square root of the whole map.
 * Additionally sets a pointer to an int to the
 * length and width of the map for later use.
 *
 * @param	str		map
 * @param	coords	lengths of x and y of the map
 *
 * @returns	true or false
 */
t_bool	bsq_map_valid(char **strs, t_coords *coords)
{
	int	i;

	if (strs == NULL)
		return (false);
	coords->y = ft_atoi(strs[0]);
	coords->x = ft_strlen(strs[1]);
	if (bsq_matrix_count(strs) - 1 != coords->y)
		return (false);
	i = 1;
	while (i < coords->y - 1)
	{
		if (ft_strlen(strs[i]) != coords->x)
			return (false);
		i++;
	}
	return (true);
}

/*
 * Gets the metadata from the map string array.
 *
 * @param	strs	array of strings
 *
 * @returns	metadata as t_tiles
 */
t_tiles	bsq_map_meta(char **strs)
{
	t_tiles	tiles;
	int		i;

	i = 0;
	while (char_is_num(strs[0][i]))
		i++;
	tiles.epty = strs[0][i];
	tiles.obst = strs[0][i + 1];
	tiles.full = strs[0][i + 2];
	return (tiles);
}

/*
 * Converts an array of strings to
 * a matrix of t_tile.
 *
 * @param	strs	array of strings
 *
 * @returns	the map
 * @returns	NULL if a character (and hence, the map) was invalid
 */
t_tile	**bsq_map_from_str(char **strs, t_coords coords, t_tiles tiles)
{
	t_tile	**map;
	int		i;
	int		j;

	strs++;
	map = bsq_map_init(coords);
	i = 0;
	while (i < coords.y)
	{
		j = 0;
		while (j < coords.x)
		{
			if (strs[i][j] != tiles.epty && strs[i][j] != tiles.obst)
			{
				bsq_map_free(map, coords);
				return (NULL);
			}
			map[i][j] = bsq_map_char_to_tile(strs[i][j], tiles);
			j++;
		}
		i++;
	}
	return (map);
}

/*
 * Reads a map from a file name.
 *
 * @param	fname	file name
 * @param	fsize	how many bytes to read
 *
 * @returns	allocated map with data
 * @returns	null if error
 */
t_map	*bsq_map_read(char *fname, int fsize)
{
	t_coords	coords;
	t_tiles		tiles;
	t_tile		**map;
	char		**strs;

	strs = bsq_read_split_free(fname, fsize);
	if (bsq_matrix_count(strs) == 0)
	{
		free_strs(strs);
		return (NULL);
	}
	if (!bsq_map_valid(strs, &coords))
		return (free_and_null(strs));
	tiles = bsq_map_meta(strs);
	map = bsq_map_from_str(strs, coords, tiles);
	if (map == NULL)
	{
		bsq_map_free(map, coords);
		free_strs(strs);
		return (NULL);
	}
	return (all_final(map, tiles, strs, coords));
}

/*
 * Reads a map from STDIN.
 *
 * @returns	allocated map with data
 * @returns	null if error
 */
t_map	*bsq_map_stdin_read(int fsize)
{
	t_coords	coords;
	t_tiles		tiles;
	t_tile		**map;
	t_map		*final;
	char		**strs;

	strs = bsq_read_split_free_stdin(fsize);
	if (bsq_matrix_count(strs) == 0)
		return (free_and_null(strs));
	if (!bsq_map_valid(strs, &coords))
		return (free_and_null(strs));
	tiles = bsq_map_meta(strs);
	map = bsq_map_from_str(strs, coords, tiles);
	if (map == NULL)
	{
		bsq_map_free(map, coords);
		free_strs(strs);
		return (NULL);
	}
	final = malloc(sizeof(t_map));
	if (final == NULL)
		return (free_and_null_map(strs, map, coords));
	free_strs(strs);
	free(strs);
	final->map = map;
	final->tiles = tiles;
	final->coords = coords;
	return (final);
}
