/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 00:28:58 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 00:37:41 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_atol
long	ft_atol(const char *str)
{
	long	val;
	bool	neg;

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
