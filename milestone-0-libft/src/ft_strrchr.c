/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:07:52 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 01:31:16 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_strrchr
char	*ft_strrchr(const char *s, char c)
{
	char	*se;

	if (!s)
		return (NULL);
	se = NULL;
	while (*s)
	{
		if (*s == (char)c)
			se = (char *)s;
		s++;
	}
	if (*s == (char)c)
		se = (char *)s;
	return (se);
}
// GPM? end ft_strrchr
