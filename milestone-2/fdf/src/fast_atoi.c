/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fast_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:53:25 by elagouch          #+#    #+#             */
/*   Updated: 2025/03/05 13:40:22 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Fast ASCII to integer conversion
 *
 * @param str Pointer to string pointer (will be updated)
 * @return int Converted integer value
 */
int	fast_atoi(const char **str)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (**str && ft_isspace(**str))
		(*str)++;
	if (**str == '-')
	{
		sign = -1;
		(*str)++;
	}
	else if (**str == '+')
		(*str)++;
	while (**str && ft_isdigit(**str))
	{
		result = result * 10 + (**str - '0');
		(*str)++;
	}
	return (sign * result);
}
