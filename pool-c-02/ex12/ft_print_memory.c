/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 20:51:05 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/02 21:11:11 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	byteInHex(uint8_t Byte)
{
	if ((Byte / 16) < 10)
		ft_putchar(48 + (Byte / 16));
	else
		ft_putchar(87 + (Byte / 16));
	if ((Byte % 16) < 10)
		ft_putchar(48 + (Byte % 16));
	else
		ft_putchar(87 + (Byte % 16));
}

void	printAddressHex(void *addr)
{
	uint8_t	*ptr;
	int		littleEndian;

	littleEndian = 7;
	ptr = (uint8_t *)&addr;
	while (littleEndian >= 0)
	{
		byteInHex(*(ptr + littleEndian));
		--littleEndian;
	}
	ft_putchar(':');
}

void	printContentHex(void *str, unsigned int size)
{
	int		i;
	short	limit;

	limit = 16;
	i = 0;
	while (--size && limit--)
	{
		if (!(i % 2))
			write(1, " ", 1);
		byteInHex(*((uint8_t *)str));
		++str;
		++i;
	}
	if (i % 2)
		write(1, "  ", 2);
	else
		write(1, " ", 1);
}

void	printContentDot(void *str, unsigned int size)
{
	short	limit;

	limit = 16;
	while (--size && limit--)
	{
		if (*(char *)str >= 32 && *(char *)str < 127)
			write(1, str, 1);
		else
			write(1, ".", 1);
		++str;
	}
	write(1, "\n", 1);
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	if (size == 1)
		return (addr);
	printAddressHex(addr);
	printContentHex(addr, size);
	printContentDot(addr, size);
	return (addr);
}
