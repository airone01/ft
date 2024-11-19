/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 12:58:00 by elagouch          #+#    #+#             */
/*   Updated: 2024/11/19 12:10:41 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

// Checks for the solution
// Returns 1 if bad, 0 otherwise
unsigned int	grid_check(unsigned int **grid, unsigned int size,
				unsigned int magic)
{
	unsigned int	count_x;
	unsigned int	count_y;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	count_x = 0;
	count_y = 0;
	while (i <= size)
	{
		j = 0;
		while (j <= size)
		{
			count_x += grid[i][j];
			count_y += grid[j][i];
			j++;
		}
		if (count_x != magic || count_y != magic)
			return (1);
		i++;
	}
	return (0);
}
