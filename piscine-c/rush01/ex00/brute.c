/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brute.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:08:02 by elagouch          #+#    #+#             */
/*   Updated: 2024/11/19 12:10:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"
#include <stdlib.h>

static const unsigned int	g_tries[24] = {
	1234, 1243, 1324, 1342, 1423, 1432,
	2134, 2143, 2314, 2341, 2413, 2431,
	3124, 3142, 3214, 3241, 3412, 3421,
	4123, 4132, 4213, 4231, 4312, 4321
};

unsigned int	brute_set_single(unsigned int try, unsigned int **grid,
	unsigned int i)
{
	if ((grid[i][1] == 0 || grid[i][1] == try / 1000) &&
		(grid[i][2] == 0 || grid[i][2] == (try / 100) % 10) &&
		(grid[i][3] == 0 || grid[i][3] == (try / 10) % 10) &&
		(grid[i][4] == 0 || grid[i][4] == try % 10))
	{
		grid[i][1] = try / 1000;
		grid[i][2] = (try / 100) % 10;
		grid[i][3] = (try / 10) % 10;
		grid[i][4] = try % 10;
		return (1);
	}
	return (0);
}

void	brute_set(unsigned int abcd[4], unsigned int **grid,
		unsigned int size, unsigned int magic)
{
	unsigned int	i;
	unsigned int	middle;
	unsigned int	t;

	(void)magic;
	middle = size - 2;
	i = 0;
	while (i < middle)
	{
		t = g_tries[abcd[i]];
		grid[i + 1][1] = t / 1000;
		grid[i + 1][2] = (t / 100) % 10;
		grid[i + 1][3] = (t / 10) % 10;
		grid[i + 1][4] = t % 10;
		i++;
	}
}

unsigned int	brute_try(unsigned int **grid, unsigned int size,
				unsigned int magic)
{
	unsigned int	abcd[4];
	unsigned int	**duped;
	unsigned int	i;

	duped = grid_dupe(grid, size);
	abcd[0] = 0;
	while (abcd[0] < 24)
	{
		abcd[1] = 0;
		while (abcd[1] < 24)
		{
			abcd[2] = 0;
			while (abcd[2] < 24)
			{
				abcd[3] = 0;
				while (abcd[3] < 24)
				{
					brute_set(abcd, duped, size, magic);
					if (!grid_check(duped, size, magic))
					{
						show_grid(duped, size);
						i = 0;
						while (i < size)
							free(duped[i++]);
						free(duped);
						return (1);
					}
					abcd[3]++;
				}
				abcd[2]++;
			}
			abcd[1]++;
		}
		abcd[0]++;
	}
	i = 0;
	while (i < size)
		free(duped[i++]);
	free(duped);
	return (0);
}
