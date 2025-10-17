/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 13:56:55 by elagouch          #+#    #+#             */
/*   Updated: 2025/10/17 16:09:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *str, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*str)
	{
		if (*str != c && !in_word)
		{
			in_word = 1;
			count++;
		}
		else if (*str == c)
			in_word = 0;
		str++;
	}
	return (count);
}

static char	*get_next_word(const char **str, char c)
{
	const char	*word_start;
	char		*word;
	size_t		len;

	while (**str == c)
		(*str)++;
	word_start = *str;
	len = 0;
	while (**str && **str != c)
	{
		len++;
		(*str)++;
	}
	word = ft_calloc(len + 1, sizeof(char));
	if (!word)
		return (NULL);
	ft_strlcpy(word, word_start, len + 1);
	return (word);
}

static void	free_split(char **split, size_t count)
{
	while (count--)
	{
		free(split[count]);
		split[count] = NULL;
	}
	free(split);
	split = NULL;
}

char	**ft_split(char *str, char c)
{
	char	**split;
	size_t	word_count;
	size_t	i;

	if (!str)
		return (NULL);
	word_count = count_words(str, c);
	split = ft_calloc(word_count + 1, sizeof(char *));
	if (!split)
		return (NULL);
	i = 0;
	while (i < word_count)
	{
		split[i] = get_next_word((const char **)&str, c);
		if (!split[i])
			return (free_split(split, i), NULL);
		i++;
	}
	split[i] = NULL;
	return (split);
}
