/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 19:14:26 by maximart          #+#    #+#             */
/*   Updated: 2025/05/06 15:06:10 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h" // for t_parse
#include "minishell.h"

/**
 * @brief Creates and initializes a new token
 *
 * @param type Token type enumeration
 * @param value String value of the token
 * @return New token pointer or NULL if allocation fails
 * @note Caller must free the returned token
 */
t_token	*create_token(t_token_type type, char *value)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	token->next = NULL;
	token->value = value;
	token->quote.in_double_quote = false;
	token->quote.in_single_quote = false;
	return (token);
}

/**
 * @brief Creates and initializes a new command
 *
 * @return New command pointer or NULL if allocation fails
 * @note Caller must free the returned token
 */
t_command	*create_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->redirection = NULL;
	cmd->next = NULL;
	cmd->args = NULL;
	cmd->arg_count = 0;
	return (cmd);
}

/**
 * @brief Creates and initializes a new command
 *
 * @param type
 * @param filename
 * @return New command pointer or NULL if allocation fails
 * @note Caller must free the returned token
 */
t_redir	*create_redirection(t_token_type type, char *filename)
{
	t_redir	*redirection;

	redirection = malloc(sizeof(t_redir));
	if (!redirection)
		return (NULL);
	redirection->type = type;
	redirection->next = NULL;
	redirection->fd = -1;
	redirection->filename = ft_strdup(filename);
	if (!redirection->filename)
	{
		free(redirection);
		return (NULL);
	}
	return (redirection);
}

void	init_parse_context(t_parse *parse, t_token *token)
{
	parse->token = token;
	parse->current = token;
}
