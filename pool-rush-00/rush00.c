/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush00.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafavier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:44:09 by cafavier          #+#    #+#             */
/*   Updated: 2024/09/14 17:50:09 by cafavier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
void	ft_putchar(char c);

//Prints the characters that are in the corners
//according to the sign of the parameters
void	pt_corner(int y, int inv_y, int line)
{
	if ((inv_y == 0) && (line == 0))
		ft_putchar ('o');
	else if ((inv_y == 1) && (line == y - 1))
		ft_putchar ('o');
	else if ((inv_y == 0) && (line == y - 1))
		ft_putchar ('o');
	else if ((inv_y == 1) && (line == 0))
		ft_putchar ('o');
}

//Define what the ft_putchar function will print
void	pt_line(int x, int y, int inv_y, int i)
{
	int	col;
	int	line;

	col = i % x;
	line = i / x;
	if (line == 0 || line == y - 1)
	{
		if (col == 0 || col == x - 1)
			pt_corner (y, inv_y, line);
		else
			ft_putchar ('-');
	}
	else
	{
		if (col == 0 || col == x - 1)
			ft_putchar ('|');
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
	int	inv_y;

	inv_y = 0;
	if (x < 0)
		x = -x;
	if (y < 0)
	{
		inv_y = 1;
		y = -y;
	}
	i = 0;
	while (i < (x * y))
	{
		col = i % x;
		pt_line (x, y, inv_y, i);
		if (col >= x - 1)
			ft_putchar ('\n');
		i++;
	}
}
