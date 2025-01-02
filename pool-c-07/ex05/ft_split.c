/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:00:50 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/02 23:15:38 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

// Copied from
// https://github.com/evgenkarlson/COMPLETED_PISCINE_C/blob/2371a32f622a085b539340f66405be7e175c169e/c07/ex05(ft_split)/ft_split.c

int	ft_is_space(char to_find, char *str)
{
	while (*str)
	{
		if (to_find == *str++)
			return (1);
	}
	return (0);
}

int	ft_wordcount(char *str, char *charset)
{
	int	count;

	count = 0;
	while (*str)
	{
		while (*str && (ft_is_space(*str, charset)))
			str++;
		if (*str && !(ft_is_space(*str, charset)))
		{
			count++;
			while (*str && !(ft_is_space(*str, charset)))
				str++;
		}
	}
	return (count);
}
char	*create_word(char *str, int i, int j)
{
	char	*word;
	int		o;

	o = 0;
	if ((word = (char *)malloc(sizeof(char) * (j - i))) == ((void *)0))
		return ((void *)0);
	while (i < j)
	{
		word[o] = str[i];
		i++;
		o++;
	}
	word[o] = '\0';
	return (word);
}

char	**ft_split(char *str, char *charset)
{
	char	**arr;
	int		index;
	int		j;
	int		i;
	int		words;

	if ((words = ft_wordcount(str, charset)))
	{
		if (!str || ((arr = (char **)malloc(sizeof(char *) * (words
							+ 1))) == ((void *)0)))
			return ((void *)0);
		i = 0;
		index = 0;
		while (index < words)
		{
			while (ft_is_space(str[i], charset) && (str[i]))
				i++;
			j = i;
			while (!(ft_is_space(str[j], charset)) && (str[j]))
				j++;
			arr[index] = create_word(str, i, j);
			i = j + 1;
			index++;
		}
	}
	else
		arr = (char **)malloc(sizeof(char *));
	arr[index] = (void *)0;
	return (arr);
}
