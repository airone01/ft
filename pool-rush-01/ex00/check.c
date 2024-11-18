/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:58:00 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/22 18:54:01 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

// Checks for the solution
// Returns 1 if bad, 0 otherwise
unsigned int	grid_check(unsigned int **grid, unsigned int size, unsigned int magic)
{
	unsigned int	countX;
	unsigned int	countY;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	countX = 0;
	countY = 0;
	while (i <= size)
	{
		j = 0;
		while (j <= size)
		{
			countX += grid[i][j];
			countY += grid[j][i];
			j++;
		}
		if (countX != magic || countY != magic)
			return (1);
		i++;
	}
	return (0);
}
