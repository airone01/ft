/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoul.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:18:43 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 13:48:14 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
