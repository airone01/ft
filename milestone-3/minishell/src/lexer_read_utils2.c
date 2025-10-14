/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_read_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:01:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/08 17:06:51 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Sets the quote flags in lexer structure
 *
 * @param lexer Pointer to lexer structure
 * @param quote_char Quote character (' or ")
 */
void	set_quote_flags(t_lexer *lexer, char quote_char)
{
	if (quote_char == '"')
		lexer->quote.in_double_quote = 1;
	else if (quote_char == '\'')
		lexer->quote.in_single_quote = 1;
}

/**
 * @brief Create a string from the quoted content
 *
 * @param lexer Pointer to lexer structure
 * @param start Start position of the content
 * @param end End position of the content
 * @return char* Allocated string containing content or NULL on error
 */
char	*create_quoted_content(t_lexer *lexer, int start, int end)
{
	char	*content;

	if (start == end)
		return (ft_strdup(""));
	content = malloc((unsigned long)(end - start + 1));
	if (!content)
		return (NULL);
	ft_strlcpy(content, lexer->input + start, (size_t)(end - start + 1));
	content[end - start] = '\0';
	return (content);
}

/**
 * @brief Handles a single part of a complex word
 *
 * @param lexer Current lexer state
 * @param result Current result string
 * @param quote_char Quote character if in quoted mode, 0 otherwise
 * @return char* Updated result string or NULL on error
 */
char	*handle_word_part_by_type(t_lexer *lexer, char *result, char quote_char)
{
	char	*new_result;
	char	*part;

	if (quote_char != 0)
	{
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
	else
		return (handle_word_part(lexer, result));
}
