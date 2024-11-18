/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 10:26:27 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/30 17:12:14 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"

/*
 * Stupid function that saves space for the norm.
 */
void	ft_strsplit_stupid(size_t ij[2], char *str, int *index, char **split)
{
	split[ij[1]++] = ft_strcut(str, *index, ij[0]);
	*index = -1;
}

/*
 * Splits a string (potentially multime times) at a character.
 * It will put the data of 0 to indicate the end of the string array.
 * @see ft_strjoin
 *
 * @param	str	string to split
 * @param	c	delimiter
 *
 * @returns	array of strings
 * @returns	if didn't find the delimiter,
 * 			array of strings with `s` inside
 */
char	**ft_strsplit(char *str, char c)
{
	size_t	ij[2];
	int		index;
	char	**split;

	if (str == NULL)
		return (NULL);
	split = malloc((ft_strcount_words_sep(str, c) + 1) * sizeof(char *));
	if (!str || !(split))
		return (0);
	ij[0] = 0;
	ij[1] = 0;
	index = -1;
	while (ij[0] <= (size_t)ft_strlen(str))
	{
		if (str[ij[0]] != c && index < 0)
			index = ij[0];
		else if ((str[ij[0]] == c || ij[0] == (size_t)ft_strlen(str))
			&& index >= 0)
			ft_strsplit_stupid(ij, str, &index, split);
		ij[0]++;
	}
	split[ij[1]] = 0;
	return (split);
}
