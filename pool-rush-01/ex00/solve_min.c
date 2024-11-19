/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_min.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:20:11 by elagouch          #+#    #+#             */
/*   Updated: 2024/11/19 12:13:55 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	get_xy(unsigned int xy[2], unsigned int index, unsigned int size);

unsigned int	solve_min_xy_cond(unsigned int xy[2],
	unsigned int **grid, unsigned int size)
{
	if (xy[0] == 0)
	{
		if (grid[1][xy[1]] != (size - 2) && grid[1][xy[1]] != 0)
			return (1);
		grid[1][xy[1]] = size - 2;
	}
	if (xy[0] == size - 1)
	{
		if (grid[size - 2][xy[1]] != (size - 2) && grid[size - 2][xy[1]] != 0)
			return (1);
		grid[size - 2][xy[1]] = size - 2;
	}
	if (xy[1] == 0)
	{
		if ((grid[xy[0]][1] != (size - 2)) && (grid[xy[0]][1] != 0))
			return (1);
		grid[xy[0]][1] = size - 2;
	}
	if (xy[1] == size - 1)
	{
		if (grid[xy[0]][size - 2] != (size - 2) && grid[xy[0]][size - 2] != 0)
			return (1);
		grid[xy[0]][size - 2] = size - 2;
	}
	return (0);
}

// Loops through all the hints and sets the max number
// when a min number (1) is hit.
// E.g.
// x-1---?---?---?-x
// | . . . . . . . |
// 1 4 . ? . ? . ? ?
// | . . . . . . . |
// ? ? . ? . ? . ? ?
// | . . . . . . . |
// ? ? . ? . ? . ? ?
// | . . . . . . . |
// ? ? . ? . ? . ? ?
// | . . . . . . . |
// x-?---?---?---?-x
// RETURNS: 1 if error
unsigned int	solve_min(unsigned int **grid, unsigned int size)
{
	unsigned int	xy[2];
	unsigned int	i;

	i = 0;
	while (i < size * 4)
	{
		get_xy(xy, i, size);
		if (grid[xy[0]][xy[1]] == 1)
		{
			if (solve_min_xy_cond(xy, grid, size))
				return (1);
		}
		i++;
	}
	return (0);
}
