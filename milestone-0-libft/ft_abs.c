/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_abs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:40:32 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/14 20:15:31 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

// GPM? begin ft_abs
/**
 * Gets the absolute value
 * @param   nb  Number to get the absolute value of
 * @return      Absolute value of nb
 */
ssize_t	ft_abs(ssize_t nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}
// GPM? end ft_abs
