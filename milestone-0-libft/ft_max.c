/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:00:27 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/19 15:04:48 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Returns the maximum of two longs
 *
 * @param	a	First long
 * @param	b	Second long
 *
 * @return	long	Maximum of a and b
 */
long	ft_max(long a, long b)
{
	if (a > b)
		return (a);
	return (b);
}

double	ft_fmax(double a, double b)
{
	if (a > b)
		return (a);
	return (b);
}
