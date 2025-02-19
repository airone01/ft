/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:07:56 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/19 14:13:57 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_strtrim
/**
 * Trims characters from the beginning and end of a string without allocating.
 *
 * @param	s1	String to be trimmed
 * @param	set	Reference set of the characters to trim
 * @returns     Trimmed string. NULL  if the allocation failed.
 */
char	*ft_strtrim(char *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*s;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	end = ft_strlen(s1);
	while (s1[start] && ft_strchr(set, s1[start]))
	{
		s1[start] = '\0';
		s = s1 + start;
		start++;
	}
	while (end > start && ft_strchr(set, s1[end - 1]))
	{
		s[end - 1] = '\0';
		end--;
	}
	return (s);
}
// GPM? end ft_strtrim
