/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_min.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 21:58:22 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 22:10:14 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief	Returns the minimum of two longs.
 *
 * @param	a	The first long.
 * @param	b	The second long.
 *
 * @returns	The minimum of the two longs.
 */
long	ft_min(long a, long b)
{
	if (a < b)
		return (a);
	return (b);
}
