/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:56:55 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 01:16:32 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_memset
void	*ft_memset(void *s, uint8_t c, size_t n)
{
	uint8_t	*pt;

	if (n != 0)
	{
		pt = s;
		while (n != 0)
		{
			*pt++ = (uint8_t)c;
			n--;
		}
	}
	return (s);
}
// GPM? end ft_memset
