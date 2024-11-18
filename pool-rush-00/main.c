/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cafavier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 08:19:40 by cafavier          #+#    #+#             */
/*   Updated: 2024/09/15 14:18:06 by gaducurt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putchar(char c);
void	rush(int x, int y);

//Check if it's a number
int	ft_is_numeric(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

//Transform a string into an integer
int	my_atoi(char *str)
{
	int	count;

	count = 0;
	while (!(*str >= '0' && *str <= '9') && *str != '\0')
		str++;
	while ((*str >= '0' && *str <= '9') && *str != '\0')
	{
		count = (count * 10) + (*str - '0');
		str++;
	}
	return (count);
}

int	check_xy(int x, int y, char **argv)
{
	if (x == 0 || y == 0)
	{
		write (1, "L'un de vos arguments n'est pas valable.\n", 41);
		return (1);
	}
	if (argv[1][0] == '-' || argv[2][0] == '-')
	{
		write(1, "Le programme ne supporte pas les arguments negatifs.\n", 53);
		return (1);
	}
	if (x > 46340 || y > 46340)
	{
		write (1, "Un de vos arguments est trop grand.\n", 34);
		write (1, "Veuillez utiliser des valeurs plus petites.\n", 44);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (argc != 3)
	{
		write (1, "Usage: rush <x> <y>\n", 20);
		return (1);
	}
	x = my_atoi(argv[1]);
	y = my_atoi(argv[2]);
	if (check_xy(x, y, argv))
		return (1);
	rush(x, y);
}
