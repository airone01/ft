/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:07:41 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/05 23:12:12 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_strmapi
/**
 * Applies the function f to each character of the string s, passing its index
 * as the first argument and the character itself as the second. A new string
 * is created (using malloc(3)) to collect the results from the successive
 * applications of f.
 * @param	s	The string on which to iterate
 * @param	f	The function to apply to each character
 * @returns     The string created from the successive applications of ’f’.
 * 			NULL if the allocation fails.
 */
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
