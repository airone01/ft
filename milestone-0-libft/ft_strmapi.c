/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 19:07:41 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/11 18:51:18 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*dst;

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
