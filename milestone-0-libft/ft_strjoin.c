/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:07:38 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/07 18:08:14 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_strjoin
/**
 * Allocates (with malloc(3)) and returns a new string, which is the result of
 * the concatenation of ’s1’ and ’s2’.
 * @param	s1	Prefix string
 * @param	s2	Suffix string
 * @returns     The new string. NULL if allocation fails.
 */
// Original implementation
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;

	if (!s1)
		s1 = "";
	if (!s2)
		s2 = "";
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = (char *)ft_calloc(s1_len + s2_len + 1, sizeof(char));
	if (!str)
		return (0);
	ft_strlcpy(str, s1, s1_len + 1);
	ft_strlcat(str, s2, s1_len + s2_len + 1);
	return (str);
}
// GPM? end ft_strjoin

//// Dependency-free implementation
// char	*ft_strjoin(char const *s1, char const *s2)
//{
//	size_t	s1_len;
//	size_t	s2_len;
//	size_t	i;
//	size_t	j;
//	char	*str;
//
//	if (!s1)
//		s1 = "";
//	if (!s2)
//		s2 = "";
//	s1_len = ft_strlen(s1);
//	s2_len = ft_strlen(s2);
//	str = (char *)ft_calloc(s1_len + s2_len + 1, sizeof(char));
//	if (!str)
//		return (0);
//	i = -1;
//	while (++i < s1_len)
//		str[i] = s1[i];
//	j = -1;
//	while (++j < s2_len)
//		str[i + j] = s2[j];
//	str[i + j] = '\0';
//	return (str);
//}

//// Kaan's implementation
// char	*ft_strjoin(char *s1, const char *s2)
//{
//	char		*join;
//	size_t		i;
//	size_t		j;
//
//	if (!s1 || !s2)
//		return (free(s1), NULL);
//	join = ft_calloc(ft_strlen(s1) + ft_strlen(s2) +1, sizeof(char));
//	if (!join)
//		return (free(s1), NULL);
//	i = 0;
//	while (s1[i])
//	{
//		join[i] = s1[i];
//		i++;
//	}
//	j = 0;
//	while (s2[j] && s2[j] != '\n')
//	{
//		join[i + j] = s2[j];
//		j++;
//	}
//	if (s2[j] == '\n')
//		join[i + j] = s2[j];
//	free(s1);
//	return (join);
//}
