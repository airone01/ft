/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_ssize.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:37:33 by elagouch          #+#    #+#             */
/*   Updated: 2024/11/20 13:33:15 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <limits.h>
#include <unistd.h>

static size_t	bad_base(char *base)
{
	size_t	i;
	size_t	j;

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

ssize_t	ft_putnbr_base_ssize_int(int nbr, char *base)
{
	ssize_t	count;
	size_t	base_len;

	if (bad_base(base))
		return (0);
	count = 0;
	base_len = ft_strlen(base);
	if (nbr == INT_MIN)
	{
		count += write(1, "-2147483648", 11);
		return (count);
	}
	if (nbr < 0)
	{
		count += write(1, "-", 1);
		count += ft_putnbr_base_ssize_int(-nbr, base);
		return (count);
	}
	if (nbr >= (int)base_len)
		count += ft_putnbr_base_ssize_int(nbr / base_len, base);
	count += write(1, &(base[nbr % base_len]), 1);
	return (count);
}

ssize_t	ft_putnbr_base_ssize_ulong(uintptr_t nbr, char *base)
{
	ssize_t	count;
	size_t	base_len;

	if (bad_base(base))
		return (0);
	count = 0;
	base_len = ft_strlen(base);
	if (nbr < 0)
	{
		count += write(1, "-", 1);
		count += ft_putnbr_base_ssize_ulong(-nbr, base);
		return (count);
	}
	if (nbr >= base_len)
		count += ft_putnbr_base_ssize_ulong(nbr / base_len, base);
	count += write(1, &(base[nbr % base_len]), 1);
	return (count);
}
