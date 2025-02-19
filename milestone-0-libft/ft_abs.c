/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:40:32 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/19 15:11:09 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// GPM? begin ft_abs
/**
 * @brief	Gets the absolute value
 *
 * @param	nb	Number to get the absolute value of
 *
 * @returns	Absolute value of nb
 */
long	ft_abs(long nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}
// GPM? end ft_abs

/**
 * @brief	Gets the absolute value
 *
 * @param	nb	Number to get the absolute value of
 *
 * @returns	Absolute value of nb
 */
double	ft_fabs(double nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}
