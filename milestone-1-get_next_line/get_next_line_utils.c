/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 09:29:20 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/15 17:36:31 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// GPM: ft_memset

// GPM: ft_calloc

// GPM: ft_strlen

// GPM: ft_strdup

// Dependency-free implementation
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;
	size_t	j;
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
	i = -1;
	while (++i < s1_len)
		str[i] = s1[i];
	j = -1;
	while (++j < s2_len)
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}
