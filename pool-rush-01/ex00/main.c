/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:22:31 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/22 18:19:16 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Prototypes :-)
#include "rush.h"

#include <stdio.h> // ;aigdoiuadbliasdbnliuasbdasd

int main(void)
{
	unsigned int	**grid;
	unsigned int	magic;
	int				size;
	char				*entry;

	//       |up   | |down | |left | |right|
	entry = "4 3 2 1 1 2 2 2 4 3 2 1 1 2 2 2"; // Original
	// entry = "8 3 2 1 8 2 2 2 8 3 2 1 1 2 2 2 8 3 2 1 1 2 2 2 8 3 2 1 1 2 2 2";
	size = read_grid_axis_size(entry) + 2;
	magic = ft_facto(size - 2);
	grid = make_grid(size);

	// show_grid(grid, size);
	// populate(grid, size);	// debug

	read_grid(entry, grid, size);
	// show_grid(grid, size);

	// Solve maybe half of the thing already
	if (solve_max(grid, size) || solve_min(grid, size))
	{
		ft_putstr("Error\n");
		return (1);
	}

	// Brute-force our way into a solution
	if (!brute_try(grid, size, magic))
	{
		ft_putstr("Error\n");
		return (1);
	}
	// show_grid(grid, size);
}

// NE PAS OUBLIER LE FREE PAR PITIE
// ET TESTER VALGRIND
// ET CHANGER LES COMMITS
// ET METTRE LE PROTO DANS LE MAIN PRINCIPAL
