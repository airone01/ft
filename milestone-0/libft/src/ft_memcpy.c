/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:56:55 by elagouch          #+#    #+#             */
/*   Updated: 2025/10/17 16:09:38 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const uint8_t	*src2;
	uint8_t			*dest2;

	if (!dest && !src)
		return (dest);
	if (n != 0)
	{
		src2 = (const uint8_t *)src;
		dest2 = (uint8_t *)dest;
		while (n-- > 0)
			*dest2++ = *src2++;
	}
	return (dest);
}
