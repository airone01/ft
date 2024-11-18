/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_non_printable.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:05:35 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/14 18:12:28 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
// #include <stdio.h>

void	ft_putchar(char c)
{
	write (1, &c, 1);
}

void	ft_putstr_non_printable(char *str)
{
	if (*str == '\0')
		return ;
	if (*str < ' ' || *str > '~')
	{
		ft_putchar ('\\');
		ft_putchar ("0123456789abcdef"[*str / 16]);
		ft_putchar ("0123456789abcdef"[*str % 16]);
	}
	else
		ft_putchar (*str);
	ft_putstr_non_printable(str + sizeof(char));
}

// int	main(void)
// {
// 	// printf ("PUTH: ");
// 	// puth(1234);
// 	ft_putstr_non_printable("Hello\n, world!");
// }
