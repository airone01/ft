/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:27:07 by maximart          #+#    #+#             */
/*   Updated: 2025/05/06 14:24:30 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Extract a word from lexer input
 *
 * @param lexer Pointer to lexer structure
 * @return Newly allocated string containing the word or NULL on error
 * @note Caller must free the returned string
 */
char	*read_word_lexer(t_lexer *lexer)
{
	int		start;
	int		length;
	char	*word;

	start = lexer->position;
	while (get_lexer(lexer) != '\0' && get_lexer(lexer) != ' '
		&& get_lexer(lexer) != '\t' && get_lexer(lexer) != '\n'
		&& get_lexer(lexer) != '|' && get_lexer(lexer) != '<'
		&& get_lexer(lexer) != '>' && get_lexer(lexer) != '&'
		&& get_lexer(lexer) != '"' && get_lexer(lexer) != '\'')
		advance_lexer(lexer);
	length = lexer->position - start;
	if (length == 0)
		return (ft_strdup(""));
	word = malloc((unsigned long)length + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, lexer->input + start, (size_t)length + 1);
	word[length] = '\0';
	return (word);
}

/**
 * @brief Extract a quoted string from lexer input
 *
 * @param lexer Pointer to lexer structure
 * @param quote_char Quote character (' or ")
 * @return Newly allocated string containing the quoted content or NULL on error
 * @note Caller must free the returned string
 */
char	*read_quoted_string_lexer(t_lexer *lexer, char quote_char)
{
	int		start;
	int		end;
	char	*content;

	start = lexer->position + 1;
	advance_lexer(lexer);
	while (get_lexer(lexer) != '\0' && get_lexer(lexer) != quote_char
		&& lexer->position < lexer->length)
		advance_lexer(lexer);
	if (lexer->position >= lexer->length)
	{
		ft_printf_fd(STDERR_FILENO,
			"minishell: syntax error near unexpected unclosed quote\n");
		return (NULL);
	}
	end = lexer->position;
	set_quote_flags(lexer, quote_char);
	advance_lexer(lexer);
	content = create_quoted_content(lexer, start, end);
	return (content);
}

/**
 * @brief Checks if the current character is part of a complex word
 *
 * @param lexer Current lexer state
 * @return int 1 if character is part of a complex word, 0 otherwise
 */
static int	peek_lexer(t_lexer *lexer)
{
	char	current;

	current = get_lexer(lexer);
	return (current != '\0' && current != ' ' && current != '\t'
		&& current != '\n' && current != '|' && current != '<' && current != '>'
		&& current != '&');
}

/**
 * @brief Processes a complex word with potential quote handling
 *
 * @param lexer Pointer to lexer structure
 * @param has_quotes Pointer to flag indicating if quotes were encountered
 * @return Processed word as a newly allocated string, or NULL on error
 */
char	*process_complex_word(t_lexer *lexer, int *has_quotes)
{
	char	*result;
	char	quote_char;

	result = NULL;
	while (peek_lexer(lexer))
	{
		if (get_lexer(lexer) == '"' || get_lexer(lexer) == '\'')
		{
			*has_quotes = 1;
			quote_char = get_lexer(lexer);
		}
		else
			quote_char = 0;
		result = handle_word_part_by_type(lexer, result, quote_char);
		if (!result)
			return (NULL);
	}
	if (!result)
		result = ft_strdup("");
	return (result);
}

/**
 * @brief Reads a complex word that might contain various elements
 *
 * @param lexer Pointer to lexer structure
 * @return Newly allocated string containing the word or NULL on error
 */
char	*read_complex_word(t_lexer *lexer)
{
	char	*result;
	int		start_pos;
	int		has_quotes;

	start_pos = lexer->position;
	has_quotes = 0;
	if (lexer->input[start_pos] == '"' && start_pos + 1 < lexer->length
		&& lexer->input[start_pos + 1] == '"')
		has_quotes = 1;
	result = process_complex_word(lexer, &has_quotes);
	if (!result && has_quotes)
		return (ft_strdup(""));
	if ((result && result[0] == '\0') && has_quotes)
	{
		free(result);
		return (ft_strdup("\1"));
	}
	if (!result)
		return (ft_strdup(""));
	return (result);
}
