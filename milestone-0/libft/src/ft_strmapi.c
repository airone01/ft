/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:07:41 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 01:30:59 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_strmapi
char	*ft_strmapi(char const *s, char (*f)(unsigned long, char))
{
	unsigned long	len;
	unsigned long	i;
	char			*dst;

	len = ft_strlen(s);
	dst = ft_calloc(len + 1, sizeof(char));
	if (!dst)
		return (0);
	i = 0;
	while (s[i])
	{
		dst[i] = f(i, s[i]);
		i++;
	}
	return (dst);
}
// GPM? end ft_strmapi
