/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:56:55 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 01:35:46 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_substr
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;

	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	s = &(s[start]);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
		return (0);
	ft_strlcpy(dst, s, len + 1);
	return (dst);
}
// GPM? end ft_substr
