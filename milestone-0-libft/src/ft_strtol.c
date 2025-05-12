/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 00:33:04 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 00:45:33 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_strtol
static int	ft_get_digit(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	return (-1);
}

static int	ft_detect_base(const char **str, int base)
{
	if ((base == 0 || base == 16) && (*str)[0] == '0' && ((*str)[1] == 'x'
			|| (*str)[1] == 'X'))
	{
		*str += 2;
		return (16);
	}
	if (base == 0 && (*str)[0] == '0')
	{
		(*str)++;
		return (8);
	}
	if (base == 0)
		return (10);
	return (base);
}

static long	ft_strtol_process(const char *str, int base, bool neg, long *result)
{
	int	digit;

	while (1)
	{
		digit = ft_get_digit(*str);
		if (digit < 0 || digit >= base)
			break ;
		if (*result > (LONG_MAX - digit) / base)
		{
			errno = ERANGE;
			if (neg)
				return (LONG_MIN);
			else
				return (LONG_MAX);
		}
		*result = *result * base + digit;
		str++;
	}
	return (0);
}

static const char	*ft_strtol_parse(const char *nptr, int *base, bool *neg)
{
	const char	*str = nptr;

	*neg = false;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			*neg = true;
		str++;
	}
	*base = ft_detect_base(&str, *base);
	return (str);
}

long	ft_strtol(const char *nptr, char **endptr, int base)
{
	const char	*str;
	long		result;
	bool		neg;
	const char	*start;
	long		overflow;

	result = 0;
	start = nptr;
	str = ft_strtol_parse(nptr, &base, &neg);
	overflow = ft_strtol_process(str, base, neg, &result);
	if (overflow)
		return (overflow);
	while (ft_get_digit(*str) >= 0 && ft_get_digit(*str) < base)
		str++;
	if (endptr)
	{
		if (str == start)
			*endptr = (char *)nptr;
		else
			*endptr = (char *)str;
	}
	if (neg)
		return (-result);
	else
		return (result);
}
// GPM? end ft_strtol
