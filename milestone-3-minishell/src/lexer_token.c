/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:31:33 by maximart          #+#    #+#             */
/*   Updated: 2025/05/06 14:25:24 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h" // for create_token
#include "lexer.h"

/**
 * @brief Handles a word token in the lexer
 *
 * @param lexer Current lexer state
 * @return t_token* Created word token or NULL on error
 */
static t_token	*handle_word_token(t_lexer *lexer)
{
	char	*word;
	t_token	*token;

	word = read_complex_word(lexer);
	if (!word)
		return (NULL);
	token = create_token(TOK_WORD, word);
	if (!token)
	{
		free(word);
		return (NULL);
	}
	return (token);
}

/**
 * @brief Extracts the next token from the lexer
 *
 * @param lexer Pointer to lexer structure
 * @return Next token or NULL on error
 * @note Caller must free the returned token
 */
t_token	*next_token_lexer(t_lexer *lexer)
{
	t_token	*token;

	skip_whitespace_lexer(lexer);
	token = handle_basics_token(lexer);
	if (token)
		return (token);
	token = handle_pipe_and_token(lexer);
	if (token)
		return (token);
	token = handle_redir_from_and_to_token(lexer);
	if (token)
		return (token);
	token = handle_word_token(lexer);
	if (token)
	{
		if (lexer->quote.in_single_quote)
			token->quote.in_single_quote = true;
		if (lexer->quote.in_double_quote)
			token->quote.in_double_quote = true;
		lexer->quote.in_single_quote = 0;
		lexer->quote.in_double_quote = 0;
		return (token);
	}
	return (NULL);
}

/**
 * @brief Frees a single token
 *
 * @param token Token to free
 */
static void	free_token(t_token *token)
{
	if (!token)
		return ;
	if (token->value)
	{
		free(token->value);
		token->value = NULL;
	}
	free(token);
}

/**
 * @brief Frees all tokens in a linked list
 *
 * This function releases the memory allocated for all tokens
 * in a linked list, starting from the given token.
 *
 * @param token First token in the list
 */
void	free_all_token(t_token *token)
{
	t_token	*current;
	t_token	*next;

	current = token;
	while (current)
	{
		next = current->next;
		free_token(current);
		current = next;
	}
}
