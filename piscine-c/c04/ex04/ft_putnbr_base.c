/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 13:37:33 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/02 22:11:59 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <unistd.h>

int	ft_strlen(char *str)
{
	if (*str == '\0')
		return (0);
	return (ft_strlen(str + sizeof(char)) + 1);
}

int	bad_base(char *base)
{
	int	i;
	int	j;

	if (base[0] == '\0' || base[1] == '\0')
		return (1);
	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '-' || base[i] == '+')
			return (1);
		j = 0;
		while (base[j] != '\0')
		{
			if (j == i && base[j + 1] != '\0')
				j++;
			else if (base[j] == base[i] && base[j + 1] != '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

ssize_t	ft_putnbr_base(uintptr_t nbr, char *base)
{
	ssize_t	count;
	size_t	base_len;

	if (bad_base(base))
		return (0);
	count = 0;
	base_len = ft_strlen(base);
	if ((long)nbr < 0)
	{
		count += write(1, "-", 1);
		count += ft_putnbr_base(-nbr, base);
		return (count);
	}
	if (nbr >= base_len)
		count += ft_putnbr_base(nbr / base_len, base);
	count += write(1, &(base[nbr % base_len]), 1);
	return (count);
}
