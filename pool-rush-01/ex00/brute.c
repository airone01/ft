/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brute.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:08:02 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/22 20:08:19 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

#include <stdio.h>

const unsigned int tries[24] = {
	1234,
	1243,
	1324,
	1342,
	1423,
	1432,
	2134,
	2143,
	2314,
	2341,
	2413,
	2431,
	3124,
	3142,
	3214,
	3241,
	3412,
	3421,
	4123,
	4132,
	4213,
	4231,
	4312,
	4321
};

// Returns: 1 when at least the value changed
unsigned int	brute_set_single(unsigned int try, unsigned int **grid, unsigned int i)
{
	// Satan
	if ((grid[i][1] == 0 || grid[i][1] == try / 1000) &&
		(grid[i][2] == 0 || grid[i][2] == (try / 100) % 100) &&
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

// // Returns: 1 when at least a value changed
// unsigned int	brute_set(unsigned int abcd[4], unsigned int **grid, unsigned int size, unsigned int magic)
// {
// 	unsigned int	i;
// 	unsigned int	try;
//
// 	i = 1;
// 	while (i < 5)
// 	{
// 		try = tries[abcd[i - 1]];
// 		// Satan
// 		if ((grid[i][1] == 0 || grid[i][1] == try / 1000) &&
// 			(grid[i][2] == 0 || grid[i][2] == (try / 100) % 100) &&
// 			(grid[i][3] == 0 || grid[i][3] == (try / 10) % 10) &&
// 			(grid[i][4] == 0 || grid[i][4] == try % 10))
// 		{
// 			grid[i][1] = try / 1000;
// 			grid[i][2] = (try / 100) % 10;
// 			grid[i][3] = (try / 10) % 10;
// 			grid[i][4] = try % 10;
// 			// printf("%d\n", (try / 10) % 10);
// 			// printf("%d%d%d%d\n", grid[i][1], grid[i][2], grid[i][3], grid[i][4]);
// 			// show_grid(grid, size);
// 			if (!grid_check(grid, size))
// 				printf("YEEEEEEEEEEEEES\n");
// 			// return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

// unsigned int	brute_inter(unsigned int abcd[4], unsigned int **grid, unsigned int size, unsigned int magic)
// {
// 	unsigned int	**duped;
//
// 	duped = grid_dupe(grid, size);
// 	brute_set(abcd, duped, size);
// 	// show_grid(duped, size);
// 	return (0);
// }

unsigned int	brute_try(unsigned int **grid, unsigned int size, unsigned int magic)
{
	unsigned int	**duped;
	unsigned int	abcd[4];

	(void) magic;
	duped = grid_dupe(grid, size);
	abcd[0] = 0;
	while (abcd[0] < 24)
	{
		brute_set_single(abcd[0], duped, 1);
		abcd[1] = 0;
		while (abcd[1] < 24)
		{
			brute_set_single(abcd[1], duped, 2);
			show_grid(grid, size);
			abcd[2] = 0;
			while (abcd[2] < 24)
			{
				brute_set_single(abcd[2], duped, 3);
				abcd[3] = 0;
				while (abcd[3] < 24)
				{
					brute_set_single(abcd[2], duped, 4);
					// unsigned int abcd[4], brute_inter(abcd, grid, size);
					abcd[3]++;
				}
				abcd[2]++;
			}
			abcd[1]++;
		}
		abcd[0]++;
	}
	return (0);
}
