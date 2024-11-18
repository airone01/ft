/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:22:54 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/30 10:22:57 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"

/*
 * Concatenates strings until the given number of characters.
 * `dest` must be a valid string that is big enough to fit
 * everything.
 *
 * @param	dest	the string to copy to
 * @param	src		the string to copy
 * @param	size	the max desired size of `dest`
 *
 * @return	the total size that the function tried to (or did) create
 */
unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	dest_len;
	unsigned int	src_len;
	unsigned int	i;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	if (size <= dest_len)
		return (src_len + size);
	while (i < (size - dest_len - 1) && src[i] != '\0')
	{
		dest[i + dest_len] = src[i];
		i++;
	}
	dest[i + dest_len] = '\0';
	return (ft_strlen(dest) - 1);
}
