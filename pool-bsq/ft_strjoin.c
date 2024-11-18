/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:46:18 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/30 13:49:18 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"

/*
 * Calculates the final size for malloc.
 * Not to be used outside of strjoin.
 * @see	ft_strjoin
 *
 * @param	size		amount of elements in the array of strings
 * @param	strs		array of strings
 * @param	size_sep	length of the separator
 */
int	get_final_size(int size, char **strs, int size_sep)
{
	int	size_final;
	int	i;

	i = 0;
	size_final = 0;
	while (i < size)
	{
		size_final += ft_strlen(strs[i]);
		if (i != size - 1)
			size_final += size_sep;
		i++;
	}
	return (size_final);
}

/*
 * Joins strings with a separator string.
 *
 * @param	size	amount of elements in the array of strings
 * @param	strs	array of strings
 * @param	sep		separator to join the strings with
 *
 * @returns	a string
 * @returns NULL if failed
 */
char	*ft_strjoin(int size, char **strs, char *sep)
{
	int		size_sep;
	int		i;
	char	*final;

	if (size == 0)
		return (malloc(sizeof(char)));
	size_sep = ft_strlen(sep);
	final = malloc(get_final_size(size, strs, size_sep) * sizeof(char));
	if (final == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		ft_strcat(final, strs[i]);
		if (i != size - 1)
			ft_strcat(final, sep);
		i++;
	}
	return (final);
}
