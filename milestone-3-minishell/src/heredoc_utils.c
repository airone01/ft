/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:00:37 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/08 17:03:58 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates the prefix part of the new string
 *
 * @param str Original string
 * @param start Start index of substring to replace
 * @return Newly allocated prefix string or NULL on error
 */
static char	*create_prefix(char *str, int start)
{
	char	*prefix;

	prefix = ft_substr(str, 0, (unsigned long)start);
	return (prefix);
}

/**
 * @brief Creates the suffix part of the new string
 *
 * @param str Original string
 * @param end End index of substring to replace
 * @return Newly allocated suffix string or NULL on error
 */
static char	*create_suffix(char *str, int end)
{
	char	*suffix;

	suffix = ft_strdup(str + end);
	return (suffix);
}

/**
 * @brief Joins prefix and replacement string
 *
 * @param prefix Prefix string
 * @param replacement Replacement string
 * @return Newly allocated joined string or NULL on error
 */
static char	*join_prefix_replacement(char *prefix, char *replacement)
{
	char	*result;

	result = ft_strjoin(prefix, replacement);
	free(prefix);
	return (result);
}

/**
 * @brief Completes the string replacement by joining with suffix
 *
 * @param temp1 First part of the string (prefix + replacement)
 * @param suffix Suffix string
 * @param original Original string to free
 * @return Newly allocated complete string or NULL on error
 */
static char	*join_with_suffix(char *temp1, char *suffix, char *original)
{
	char	*result;

	result = ft_strjoin(temp1, suffix);
	free(temp1);
	free(suffix);
	free(original);
	return (result);
}

/**
 * @brief Replaces a substring in a string with another substring
 *
 * @param str Original string
 * @param start Start index of substring to replace
 * @param end End index of substring to replace
 * @param replacement Replacement string
 * @return Newly allocated string with replacement
 */
char	*replace_substring(char *str, int start, int end, char *replacement)
{
	char	*prefix;
	char	*suffix;
	char	*temp1;

	prefix = create_prefix(str, start);
	if (!prefix)
		return (NULL);
	suffix = create_suffix(str, end);
	if (!suffix)
	{
		free(prefix);
		return (NULL);
	}
	temp1 = join_prefix_replacement(prefix, replacement);
	if (!temp1)
	{
		free(suffix);
		return (NULL);
	}
	return (join_with_suffix(temp1, suffix, str));
}
