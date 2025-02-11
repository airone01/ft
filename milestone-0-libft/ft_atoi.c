/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/05 22:54:44 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_atoi
// GPM? begin ft_atol
/**
 * Classical atol implementation.
 *
 * @param	str	String to infer number from
 *
 * @returns		Infered number
 * @returns		0 if failed (or if there was no number)
 */
long	ft_atol(const char *str)
{
	long	val;
	t_bool	neg;

	val = 0;
	neg = false;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = true;
		str++;
	}
	while (ft_isdigit(*str))
		val = (val * 10) + (*str++ - '0');
	if (neg)
		val = -val;
	return (val);
}
// GPM? end ft_atol

/**
 * Infers a number from a sing.
 *
 * @param	str	String to infer number from
 *
 * @returns		Infered number
 * @returns		0 if failed (or if there was no number)
 */
int	ft_atoi(const char *str)
{
	long	val;

	val = ft_atol(str);
	if (val > INT_MAX || val < INT_MIN)
		return (0);
	return ((int)val);
}
// GPM? end ft_atoi
