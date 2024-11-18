/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:25:56 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/30 10:25:57 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
 * Allocates a new string array and initializes it.
 *
 * @param	size	number of chars of the new string including the '\0'
 *
 * @returns	allocated string
 */
char	*ft_strnew(int size)
{
	int		i;
	char	*dest;

	dest = malloc(size * sizeof(char));
	if (dest != NULL)
	{
		i = 0;
		while (i < size)
		{
			dest[i] = '\0';
			i++;
		}
	}
	return (dest);
}
