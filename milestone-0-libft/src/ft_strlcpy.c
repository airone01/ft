/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 01:30:52 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_strlcpy
unsigned long	ft_strlcpy(char *dst, const char *src, unsigned long size)
{
	const char	*src_start = src;

	if (size > 0)
	{
		while (--size > 0 && *src)
		{
			*dst++ = *src++;
		}
		*dst = '\0';
	}
	while (*src)
		src++;
	return ((unsigned long)(src - src_start));
}
// GPM? end ft_strlcpy
