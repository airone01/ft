/* ************************************************************************** */
/*                                                                            */
/*                                                     _    ⣀⣀⣀⡀⡀⡀⡀⣀⡀⣀⣀⣀⡀  */
/*   ft_split.c                                    _ _/ |   ⡇⣶⡆⡇⡾⢏⡭⡵⠀⡇⣶⡆⡇  */
/*                                                | '_| |_  ⣓⣒⠒⡃⡂⣏⡆⡯⢇⠓⠶⠖⡃  */
/*   By: elagouch <elagouch@student.42lyon.fr>    |_|_|_(@) ⢻⣊⡞⣪⢳⡗⣳⢤⣈⢍⣰⢖⡇  */
/*                                                | | |_  ) ⠜⡲⡢⣲⡯⡼⡑⡁⣝⣘⡚⢠⠅  */
/*   Created: 2024/11/12 10:48:43 by elagouch     |_  _/ /  ⡖⣒⡒⡆⠉⠧⢰⣮⣇⣂⡏⡳⡆  */
/*   Updated: 2024/11/12 18:11:47 by elagouch       |_/___| ⣇⣛⣃⡇⡿⢤⠤⠾⠡⠹⢝⣚⡁  */
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
		free(split[count]);
	free(split);
}

/*
 * Allocates (with malloc(3)) and returns an array of strings obtained by
 * splitting ’s’ using the character ’c’ as a delimiter. The array must end
 * with a NULL pointer.
 *
 * @param	str	string to split
 * @param	c	delimiter
 *
 * @returns	array of strings
 * @returns	if didn't find the delimiter,
 * 			array of strings with `s` inside
 */
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
		{
			free_split(split, i);
			return (NULL);
		}
		i++;
	}
	return (split);
}
