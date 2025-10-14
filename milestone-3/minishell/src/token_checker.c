/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 08:32:58 by maximart          #+#    #+#             */
/*   Updated: 2025/05/06 15:00:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker.h"
#include "lexer.h"

void	print_token_error(const char *s)
{
	ft_printf_fd(STDERR_FILENO,
		"minishell: syntax error near unexpected token `%s'\n", s);
}

/**
 * @brief Checks for duplicate redirection tokens
 *
 * @param current Current token
 * @return bool false if duplicated redirection found, true otherwise
 */
static bool	check_duplicate_redirs(t_token *current)
{
	if (current->type == TOK_REDIR_FROM
		&& current->next->type == TOK_REDIR_FROM)
	{
		print_token_error("&");
		print_token_error("<");
		return (false);
	}
	if (current->type == TOK_REDIR_TO && current->next->type == TOK_REDIR_TO)
	{
		print_token_error(">");
		return (false);
	}
	if (current->type == TOK_HERE_DOC_TO
		&& current->next->type == TOK_HERE_DOC_TO)
	{
		print_token_error(">>");
		return (false);
	}
	if (current->type == TOK_HERE_DOC_FROM
		&& current->next->type == TOK_HERE_DOC_FROM)
	{
		print_token_error("<<");
		return (false);
	}
	return (true);
}

/**
 * @brief Checks for missing target after redirection
 *
 * @param ctx Context
 * @param current Current token
 * @return bool false if missing target found, true otherwise
 */
static bool	check_missing_target(t_token *current)
{
	if (token_is_redirection(current->type)
		&& (token_is_redirection(current->next->type)
			|| current->next->type == TOK_PIPE || current->next->type == TOK_EOF
			|| current->next->type == TOK_NEW_LINE))
	{
		print_token_error("newline");
		return (false);
	}
	return (true);
}

/**
 * @brief Checks for invalid redirection sequences
 *
 * @param tokens Token list to validate
 * @return bool false if invalid redirection found, true otherwise
 */
static bool	check_invalid_tokens(t_token *tokens)
{
	t_token	*current;

	current = tokens;
	while (current && current->next)
	{
		if (!check_logical_tokens(current))
			return (false);
		if (!check_redir_combinations(current))
			return (false);
		if (!check_pipe_tokens(current))
			return (false);
		if (!check_duplicate_redirs(current))
			return (false);
		if (!check_missing_target(current))
			return (false);
		current = current->next;
	}
	return (true);
}

/**
 * @brief Validates token sequence and prints error if invalid
 *
 * @param tokens Token list to validate
 * @return bool true if valid sequence, false if invalid
 */
bool	validate_token_sequence(t_token *tokens)
{
	if (!tokens)
		return (false);
	if (!check_invalid_tokens(tokens))
		return (false);
	return (true);
}
