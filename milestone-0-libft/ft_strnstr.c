/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 18:49:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/14 20:25:49 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_strnstr
/**
 * The strnstr() function locates the first occurrence of the null-terminated
 * string little in the string big, where not more than len characters are
 * searched.  Characters that appear after a ‘\0’ character are not searched.
 * Since the strnstr() function is a FreeBSD specific API,
 * it should only be used when portability is not a concern.
 * @param	big		String to search in
 * @param	little	Substring to search for
 * @param	len		Most characters to search
 * @returns         If little is an empty string, big is returned; if little
 * occurs nowhere in big, NULL is returned; otherwise a pointer to the first
 * character of the first occurrence of little is returned.
 */
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (!*little)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		if (big[i] == little[j])
		{
			while (big[i + j] == little[j] && (i + j) < len)
			{
				j++;
				if (!little[j])
					return ((char *)&big[i]);
			}
		}
		i++;
	}
	return (NULL);
}
// GPM? end ft_strnstr
