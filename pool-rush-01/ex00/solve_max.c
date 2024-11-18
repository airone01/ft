/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_max.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 15:20:11 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/22 13:43:39 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Prototypes :-)
void	get_xy(unsigned int xy[2], unsigned int index, unsigned int size);

// Solves one uint depending on the where we currently are
// Returns 1 if something was changed, 0 otherwise.
void	solve_max_place(unsigned int xy[2], unsigned int **grid, unsigned int size, unsigned int j)
{
	if (xy[0] == 0)
		grid[j][xy[1]] = j;
	if (xy[0] == size - 1)
		grid[size - 1 - j][xy[1]] = j;
	if (xy[1] == 0)
		grid[xy[0]][j] = j;
	if (xy[1] == size - 1)
		grid[xy[0]][size - 1 - j] = j;
}

// After a max number (n) is hit, this function loops through the table to
// set the all the buildings in the corresponding line/row by calling
// solve_max_place.
// E.g.
// x-4---?---?---?-x
// | . . . . . . . |
// 4 1 . 2 . 3 . 4 ?
// | . . . . . . . |
// ? 2 . ? . ? . ? ?
// | . . . . . . . |
// ? 3 . ? . ? . ? ?
// | . . . . . . . |
// ? 4 . ? . ? . ? ?
// | . . . . . . . |
// x-?---?---?---?-x
void	solve_max_xy(unsigned int xy[2], unsigned int **grid, unsigned int size)
{
	unsigned int	j;
	unsigned int	middle_size;

	middle_size = size - 2;
	if (grid[xy[0]][xy[1]] == middle_size)
	{
		j = 1;
		while (j < middle_size + 1)
		{
			solve_max_place(xy, grid, size, j);
			j++;
		}
	}
}

// Calls solve_max_xy on every uint of the hints.
unsigned int	solve_max(unsigned int **grid, unsigned int size)
{
	unsigned int	xy[2];
	unsigned int	i;

	i = 0;
	while (i < size * 4)
	{
		get_xy(xy, i, size);
		solve_max_xy(xy, grid, size);
		i++;
	}
	return (0);
}
