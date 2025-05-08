/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:17:06 by maximart          #+#    #+#             */
/*   Updated: 2025/05/06 15:06:26 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Return current character at lexer position
 *
 * @param lexer Pointer to lexer structure
 * @return Current character or '\0' if at end of input
 */
char	get_lexer(t_lexer *lexer)
{
	if (lexer->position >= lexer->length)
		return ('\0');
	return (lexer->input[lexer->position]);
}

/**
 * @brief Advance lexer position by one character
 *
 * @param lexer Pointer to lexer structure
 */
void	advance_lexer(t_lexer *lexer)
{
	if (lexer->position < lexer->length)
		lexer->position++;
}

/**
 * @brief Skip whitespaces characters in lexer input
 *
 * @param lexer Pointer to lexer structure
 */
void	skip_whitespace_lexer(t_lexer *lexer)
{
	while (get_lexer(lexer) == ' ' || get_lexer(lexer) == '\t')
		advance_lexer(lexer);
}

void	sync_quote_state(t_ctx *ctx, t_lexer *lexer)
{
	ctx->quote.in_single_quote = lexer->quote.in_single_quote;
	ctx->quote.in_double_quote = lexer->quote.in_double_quote;
}
