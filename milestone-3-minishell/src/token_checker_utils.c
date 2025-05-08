/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 15:52:57 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:00:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include "lexer.h"

/**
 * @brief Checks for errors with &, ||, and && tokens
 *
 * @param token The token to check
 * @return bool false if invalid token found, true otherwise
 */
bool	check_logical_tokens(t_token *token)
{
	if (token->type == TOK_ESP)
	{
		print_token_error("&");
		return (false);
	}
	if (token->type == TOK_OR)
	{
		print_token_error("||");
		return (false);
	}
	if (token->type == TOK_AND)
	{
		print_token_error("&&");
		return (false);
	}
	return (true);
}

/**
 * @brief Checks for invalid redirection combinations
 *
 * @param current Current token
 * @return bool false if invalid redirection found, true otherwise
 */
bool	check_redir_combinations(t_token *current)
{
	if (current->type == TOK_REDIR_FROM && current->next->type == TOK_REDIR_TO)
	{
		print_token_error("newline");
		return (false);
	}
	if (token_is_redirection(current->type)
		&& current->next->type == TOK_REDIR_TO)
	{
		print_token_error(">");
		return (false);
	}
	if (token_is_redirection(current->type)
		&& current->next->type == TOK_REDIR_FROM)
	{
		print_token_error("<");
		return (false);
	}
	return (true);
}

/**
 * @brief Checks for invalid pipe token combinations
 *
 * @param current Current token
 * @return bool false if invalid pipe found, true otherwise
 */
bool	check_pipe_tokens(t_token *current)
{
	if ((current->type == TOK_PIPE && token_is_redirection(current->next->type)
			&& current->next->next->type == TOK_EOF)
		|| (token_is_redirection(current->type)
			&& current->next->type == TOK_PIPE
			&& current->next->next->type == TOK_EOF))
	{
		print_token_error("|");
		return (false);
	}
	if (current->type == TOK_PIPE && (current->next->type == TOK_PIPE
			|| current->next->type == TOK_EOF))
	{
		print_token_error("|");
		return (false);
	}
	return (true);
}
