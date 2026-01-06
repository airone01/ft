/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_read_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 10:43:47 by maximart          #+#    #+#             */
/*   Updated: 2025/05/06 14:24:40 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Joins two strings and frees the first one
 *
 * @param s1 First string (will be freed)
 * @param s2 Second string
 * @return Newly allocated joined string or NULL on error
 */
char	*join_and_free(char *s1, char *s2)
{
	char	*result;

	if (!s1)
		return (ft_strdup(s2));
	result = ft_strjoin(s1, s2);
	free(s1);
	return (result);
}

/**
 * @brief Handle dollar sign during complex word reading
 *
 * @param result Current result buffer
 * @return Updated result buffer with position at dollar sign
 */
char	*handle_dollar_sign(char *result)
{
	if (!result)
		result = ft_strdup("");
	return (result);
}

/**
 * @brief Handle word part during complex word reading
 *
 * @param lexer Pointer to lexer structure
 * @param result Current result buffer
 * @return Updated result buffer or NULL on error
 */
char	*handle_word_part(t_lexer *lexer, char *result)
{
	char	*part;
	char	*new_result;

	part = read_word_lexer(lexer);
	if (!part)
	{
		free(result);
		return (ft_strdup(""));
	}
	new_result = join_and_free(result, part);
	free(part);
	return (new_result);
}

/**
 * @brief Handle quoted part during complex word reading
 *
 * @param lexer Pointer to lexer structure
 * @param result Current result buffer
 * @param quote_char Quote character (single or double)
 * @return Updated result buffer or NULL on error
 */
char	*handle_quoted_part(t_lexer *lexer, char *result, char quote_char)
{
	char	*part;
	char	*new_result;

	part = read_quoted_string_lexer(lexer, quote_char);
	if (!part)
	{
		free(result);
		return (NULL);
	}
	new_result = join_and_free(result, part);
	free(part);
	return (new_result);
}

/**
 * @brief Handles dollar sign followed by quotes pattern
 *
 * @param lexer Current lexer state
 * @param result Current result string (can be NULL)
 * @return char* Token string or NULL on error
 */
char	*handle_dollar_quotes(t_lexer *lexer)
{
	char	quote_char;

	advance_lexer(lexer);
	quote_char = get_lexer(lexer);
	advance_lexer(lexer);
	while (get_lexer(lexer) != '\0' && get_lexer(lexer) != quote_char)
		advance_lexer(lexer);
	if (get_lexer(lexer) == quote_char)
		advance_lexer(lexer);
	return (ft_strdup(""));
}
