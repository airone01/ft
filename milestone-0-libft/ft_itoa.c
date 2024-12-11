/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/11 18:24:42 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_num_len(int n, const char *b)
{
	size_t	len;
	size_t	bl;
	long	num;

	len = 0;
	if (n <= 0)
		len = 1;
	bl = ft_strlen(b);
	num = n;
	if (n < 0)
		num = -(long)n;
	while (num > 0)
	{
		num /= bl;
		len++;
	}
	return (len);
}

static void	fill_number(char *s, int n, int len, const char *b)
{
	size_t	bl;
	long	num;
	int		is_negative;

	bl = ft_strlen(b);
	is_negative = 0;
	if (n < 0)
		is_negative = 1;
	num = n;
	if (is_negative)
		num = -(long)n;
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

/**
 * Allocates (with malloc(3)) and returns a string representing the integer
 * received as an argument. Negative numbers must be handled.
 * (base-dependant version)
 * @param	n	Number
 * @param	b	Base
 * @returns     Inferred string
 */
char	*ft_itoa_base(int n, const char *b)
{
	size_t	len;
	char	*s;

	len = get_num_len(n, b);
	s = ft_calloc(len + 1, sizeof(char));
	if (!s)
		return (0);
	fill_number(s, n, len, b);
	return (s);
}

/*
 * Allocates (with malloc(3)) and returns a string representing the integer
 * received as an argument. Negative numbers must be handled.
 * @param	n	Number
 * @returns     Inferred string
 */
char	*ft_itoa(int n)
{
	return (ft_itoa_base(n, "0123456789"));
}
