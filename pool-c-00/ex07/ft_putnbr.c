/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 18:01:45 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/11 19:37:16 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// const int int_min = -2147483648;
// const int int_max = 2147483647;

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putnbr(int nbr)
{
	if (nbr == -2147483648)
	{
		write (1, "-2147483648", 11);
		return ;
	}
	if (nbr < 0)
	{
		ft_putchar ('-');
		ft_putnbr (-(nbr));
		return ;
	}
	if (nbr >= 10)
	{
		ft_putnbr (nbr / 10);
		ft_putchar ((nbr % 10) + '0');
		return ;
	}
	ft_putchar (nbr + '0');
}

// int	main(void)
// {
// 	// ft_putnbr (-420);
// 	ft_putnbr (int_min);
// 	// ft_putnbr (int_max);
// }
