/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 18:07:16 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/22 20:02:48 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RUSH_H

unsigned int	grid_check(unsigned int **grid, unsigned int size, unsigned int magic);
unsigned int	brute_try(unsigned int **grid, unsigned int size, unsigned int magic);
unsigned int	**grid_dupe(unsigned int **grid, unsigned int size);
unsigned int	ft_pow(const unsigned int x, const unsigned int y);
unsigned int	solve_max(unsigned int **grid, unsigned int size);
unsigned int	solve_min(unsigned int **grid, unsigned int size);
unsigned int	**make_grid(unsigned int size);
unsigned int	read_grid_axis_size(char *str);
unsigned int	ft_facto(unsigned int size);
void	read_grid(char *str, unsigned int **grid, unsigned int size);
void	show_grid(unsigned int **grid, unsigned int size);
void	ft_putstr(char *str);
void	ft_putchar(char c);

#endif
