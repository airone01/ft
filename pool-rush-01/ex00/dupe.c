/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dupe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:14:54 by elagouch          #+#    #+#             */
/*   Updated: 2024/11/19 11:34:31 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

// Duplicate a grid
unsigned int	**grid_dupe(unsigned int **grid, unsigned int size)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	**duped;

	duped = make_grid(size);
	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			duped[i][j] = grid[i][j];
			j++;
		}
		i++;
	}
	return (duped);
}
