/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_tab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/03 10:21:00 by elagouch          #+#    #+#             */
/*   Updated: 2024/10/03 10:21:03 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_stock_str.h"
#include <stdlib.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	if (*str == '\0')
		return (0);
	return (ft_strlen(str + sizeof(char)) + 1);
}

void	ft_putstr(char *str)
{
	write(1, str, ft_strlen(str));
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int nb)
{
	if (nb == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (nb < 0)
	{
		ft_putchar('-');
		ft_putnbr(-nb);
		return ;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putchar(nb % 10 + '0');
		return ;
	}
	ft_putchar(nb + '0');
}

void	ft_show_tab(struct s_stock_str *par)
{
	int		i;
	char	**strs;

	strs = malloc(20 * sizeof(char *));
	if (strs == NULL)
		return ;
	i = 0;
	while (par[i].str != NULL)
	{
		ft_putstr(par[i].str);
		ft_putstr("\n");
		ft_putnbr(par[i].size);
		ft_putstr("\n");
		ft_putstr(par[i].copy);
		ft_putstr("\n");
		i++;
	}
}

// #include <stdio.h>
// int main(void)
// {
//   int i = 0;
//   char **strs = malloc(20 * sizeof(char *));
//   while (i < 20)
//   {
//     strs[i] = malloc(30 * sizeof(char));
//     strs[i][0] = '\0';
//     sprintf(strs[i], "hello, world: [%d]", i);
//     i++;
//   }
//   t_stock_str *tab = ft_strs_to_tab(20, strs);
//   ft_show_tab(tab);
// }
