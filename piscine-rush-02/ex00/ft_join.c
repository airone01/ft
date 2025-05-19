/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_join.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 11:13:23 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/29 22:54:34 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"

/*
 * Calculates the final size for malloc.
 * Not to be used outside of strjoin
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
