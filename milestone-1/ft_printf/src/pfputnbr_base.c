/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pfputnbr_base.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:37:33 by elagouch          #+#    #+#             */
/*   Updated: 2026/03/16 17:55:35 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"
#include <limits.h>
#include <unistd.h>

static unsigned long	bad_base(const char *base)
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

ssize_t	pfputnbr_base(int fd, int nbr, const char *base)
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
		count += pfputnbr_base(fd, -nbr, base);
		return (count);
	}
	if (nbr >= (int)base_len)
		count += pfputnbr_base(fd, nbr / (int)base_len, base);
	count += write(fd, &(base[nbr % base_len]), 1);
	return (count);
}

ssize_t	pfputnbru_base(int fd, unsigned long nbr, const char *base)
{
	size_t	base_len;
	ssize_t	count;

	if (bad_base(base))
		return (0);
	count = 0;
	base_len = ft_strlen(base);
	if (nbr >= base_len)
		count += pfputnbru_base(fd, nbr / base_len, base);
	count += write(fd, &(base[nbr % base_len]), 1);
	return (count);
}
