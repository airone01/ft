/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_ssize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:37:33 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/08 16:58:23 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>
#include <unistd.h>

static unsigned long	bad_base(char *base)
{
	unsigned long	i;
	unsigned long	j;

	if (!base || !base[0] || !base[1])
		return (1);
	i = 0;
	while (base[i])
	{
		if (base[i] == '-' || base[i] == '+')
			return (1);
		j = 0;
		while (base[j])
		{
			if (j == i && base[j + 1])
				j++;
			else if (base[j] == base[i] && base[j + 1])
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

long	ft_putnbr_base_ssize_int(int fd, int nbr, char *base)
{
	long	base_len;
	long	count;

	if (bad_base(base))
		return (0);
	count = 0;
	base_len = (long)ft_strlen(base);
	if (nbr == INT_MIN)
	{
		count += write(fd, "-2147483648", 11);
		return (count);
	}
	if (nbr < 0)
	{
		count += write(fd, "-", 1);
		count += ft_putnbr_base_ssize_int(fd, -nbr, base);
		return (count);
	}
	if (nbr >= (int)base_len)
		count += ft_putnbr_base_ssize_int(fd, nbr / (int)base_len, base);
	count += write(fd, &(base[nbr % base_len]), 1);
	return (count);
}

long	ft_putnbr_base_ssize_ulong(int fd, uintptr_t nbr, char *base)
{
	long	base_len;
	long	count;

	if (bad_base(base))
		return (0);
	count = 0;
	base_len = (long)ft_strlen(base);
	if ((long)nbr < 0)
	{
		count += write(fd, "-", 1);
		count += ft_putnbr_base_ssize_ulong(fd, -nbr, base);
		return (count);
	}
	if (nbr >= (uintptr_t)base_len)
		count += ft_putnbr_base_ssize_ulong(fd, nbr / (uintptr_t)base_len,
				base);
	count += write(fd, &(base[nbr % (uintptr_t)base_len]), 1);
	return (count);
}
