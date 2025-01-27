/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:07:56 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/14 20:26:15 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_strtrim
/**
 * Allocates (with malloc(3)) and returns a copy of ’s1’ with the characters
 * specified in ’set’ removed from the beginning and the end of the string.
 * @param	s1	String to be trimmed
 * @param	set	Reference set of the characters to trim
 * @returns     Trimmed string. NULL  if the allocation failed.
 */
char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*s;

	if (!s1 || !set)
		return (0);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	s = ft_calloc(end - start + 1, sizeof(char));
	if (!s)
		return (0);
	ft_strlcpy(s, &s1[start], end - start + 1);
	return (s);
}
// GPM? end ft_strtrim
