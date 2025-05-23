/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:56:55 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 01:14:28 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_memchr
void	*ft_memchr(const void *s, uint8_t c, size_t n)
{
	uint8_t	*se;

	if (!s)
		return (NULL);
	se = (uint8_t *)s;
	while (n--)
	{
		if (*se == (uint8_t)c)
			return (se);
		se++;
	}
	return (0);
}
// GPM? end ft_memchr
