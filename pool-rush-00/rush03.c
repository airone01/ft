/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush03.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafavier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:51:22 by cafavier          #+#    #+#             */
/*   Updated: 2024/09/14 18:17:52 by cafavier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_putchar(char c);

//Prints the characters that are in the corners
//according to the sign of the parameters
void	pt_corner(int x, int inv_x, int col)
{
	if ((inv_x == 0) && (col == 0))
		ft_putchar ('A');
	else if ((inv_x == 1) && (col == x - 1))
		ft_putchar ('A');
	else if ((inv_x == 0) && (col == x - 1))
		ft_putchar ('C');
	else if ((inv_x == 1) && (col == 0))
		ft_putchar ('C');
}

//Define what the ft_putchar function will print
void	pt_line(int x, int y, int inv_x, int i)
{
	int	col;
	int	line;

	col = i % x;
	line = i / x;
	if (line == 0 || line == y - 1)
	{
		if (col == 0 || col == x - 1)
			pt_corner (x, inv_x, col);
		else
			ft_putchar ('B');
	}
	else
	{
		if (col == 0 || col == x - 1)
			ft_putchar ('B');
		else
			ft_putchar (' ');
	}
}

//Check the sign and make them positive and call the pt_line function
//If end of column, display \n
void	rush(int x, int y)
{
	int	i;
	int	col;
	int	inv_x;

	inv_x = 0;
	if (x < 0)
	{
		inv_x = 1;
		x = -x;
	}
	if (y < 0)
		y = -y;
	i = 0;
	while (i < (x * y))
	{
		col = i % x;
		pt_line (x, y, inv_x, i);
		if (col >= x - 1)
			ft_putchar ('\n');
		i++;
	}
}
