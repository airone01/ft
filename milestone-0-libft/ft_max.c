/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_max.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 22:00:01 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 22:09:57 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Returns the maximum of two longs.
 *
 * @param	a	The first long.
 * @param	b	The second long.
 *
 * @returns	The maximum of the two longs.
 */
long	ft_max(long a, long b)
{
	if (a > b)
		return (a);
	return (b);
}
