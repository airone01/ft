/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_map_put.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 19:45:25 by elagouch          #+#    #+#             */
/*   Updated: 2024/10/01 11:52:18 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"

/*
 * Puts a tile to the string. Needs the map to convert it to a character.
 *
 * @param	c		character to translate
 * @param	map		map used for translation
 *
 * @returns	translated tile
 */
t_tile	bsq_map_char_to_tile(char c, t_tiles tiles)
{
	if (c == tiles.epty)
		return (epty);
	if (c == tiles.full)
		return (full);
	return (obst);
}

/*
 * Gets the char for a tile. Needs the map to convert it to a character.
 *
 * @param	tile	type of the tile to display
 * @param	map		map used for translation
 *
 * @returns	char corresponding to the tile
 */
char	bsq_map_tile_to_char(t_tile tile, t_tiles tiles)
{
	if (tile == epty)
		return (tiles.epty);
	if (tile == full)
		return (tiles.full);
	return (tiles.obst);
}

/*
 * Displays a map on STDOUT.
 *
 * @param	map	the map to display
 */
void	bsq_map_put(t_map map)
{
	char	c;
	int		i;
	int		j;

	i = 0;
	while (i < map.coords.y)
	{
		j = 0;
		while (j < map.coords.x)
		{
			c = bsq_map_tile_to_char(map.map[i][j], map.tiles);
			ft_putchar(c);
			j++;
		}
		ft_putstr("\n");
		i++;
	}
}
