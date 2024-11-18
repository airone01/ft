/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 10:24:45 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/22 18:28:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rush.h"

// x to the power of y
unsigned int	ft_pow(const unsigned int x, const unsigned int y)
{
	if (y == 0)
		return (1);
	return (ft_pow(x, y - 1) * x);
}

unsigned int	ft_facto(unsigned int size)
{
	if (size == 1)
		return (1);
	return (ft_facto(size - 1) * size);
}
