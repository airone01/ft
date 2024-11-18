/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 09:52:57 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/29 10:01:25 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
 * Allocates a new string array and initializes it.
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
