/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:56:55 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/05 01:31:53 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_strdup
/**
 * Duplicates a string.
 * @param	s	String to duplicate
 * @returns     String if everything worked
 * @returns     NULL if malloc failed
 */
char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*dst;

	dst = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!dst)
		return (0);
	i = 0;
	while (s[i])
	{
		dst[i] = s[i];
		i++;
	}
	return ((char *)dst);
}
// GPM? end ft_strdup
