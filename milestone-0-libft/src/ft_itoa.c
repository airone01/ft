/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 01:09:47 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_itoa
// GPM? begin ft_itoa_base
static long	get_num_len(int n, const char *b)
{
	long	len;
	long	bl;
	long	num;

	len = 0;
	if (n <= 0)
		len = 1;
	bl = (long)ft_strlen(b);
	num = n;
	if (n < 0)
		num = -n;
	while (num > 0)
	{
		num /= bl;
		len++;
	}
	return (len);
}

static void	fill_number(char *s, int n, long len, const char *b)
{
	long	bl;
	long	num;
	int		is_negative;

	bl = (long)ft_strlen(b);
	is_negative = 0;
	if (n < 0)
		is_negative = 1;
	num = n;
	if (is_negative)
		num = -n;
	s[len] = '\0';
	while (len > is_negative)
	{
		len--;
		s[len] = b[num % bl];
		num /= bl;
	}
	if (is_negative)
		s[0] = '-';
}

char	*ft_itoa_base(int n, const char *b)
{
	long	len;
	char	*s;

	if (!b)
		return (NULL);
	len = get_num_len(n, b);
	s = ft_calloc((size_t)(len + 1), sizeof(char));
	if (!s)
		return (0);
	fill_number(s, n, len, b);
	return (s);
}
// GPM? end ft_itoa_base

char	*ft_itoa(int n)
{
	return (ft_itoa_base(n, "0123456789"));
}
// GPM? end ft_itoa
