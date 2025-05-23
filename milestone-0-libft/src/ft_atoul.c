/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 00:28:38 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 00:29:41 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_atoul
unsigned long	ft_atoul(const char *str)
{
	unsigned long	val;

	val = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+')
		str++;
	while (ft_isdigit(*str))
		val = (val * 10) + (unsigned long)(*str++ - '0');
	return (val);
}
// GPM? end ft_atoul
