/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtoul.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 00:37:55 by elagouch          #+#    #+#             */
/*   Updated: 2025/10/17 16:08:17 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_get_digit_ul(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'Z')
		return (c - 'A' + 10);
	return (-1);
}

static int	ft_detect_base_ul(const char **str, int base)
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

static const char	*ft_skip_whitespace(const char *str)
{
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	return (str);
}

static unsigned long	ft_parse_digits(const char **str, int base,
		unsigned long *result)
{
	long	digit;

	*result = 0;
	digit = ft_get_digit_ul(**str);
	while (digit >= 0 && digit < base)
	{
		if ((long)*result > ((long)ULONG_MAX - digit) / base)
		{
			errno = ERANGE;
			return (ULONG_MAX);
		}
		*result = (unsigned long)((long)*result * base + digit);
		(*str)++;
		digit = ft_get_digit_ul(**str);
	}
	return (*result);
}

unsigned long	ft_strtoul(const char *nptr, char **endptr, int base)
{
	const char		*str = ft_skip_whitespace(nptr);
	unsigned long	result;
	const char		*start = str;

	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		errno = ERANGE;
		if (endptr)
			*endptr = (char *)str;
		return (0);
	}
	base = ft_detect_base_ul(&str, base);
	result = ft_parse_digits(&str, base, &result);
	if (str == start && endptr)
		*endptr = (char *)nptr;
	else if (endptr)
		*endptr = (char *)str;
	return (result);
}
