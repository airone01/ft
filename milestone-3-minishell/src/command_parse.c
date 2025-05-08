/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 13:46:45 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:00:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "commands.h"
#include "free.h"
#include "lexer.h"

/**
 * @brief Processes redirection token
 *
 * @param cmd Current command being built
 * @param current Current token
 * @param has_redirections Flag to track if redirections exist
 * @param ctx Context containing environment information
 * @return bool true on success, false on failure
 */
static bool	process_redirection_token_case(t_command *cmd,
		t_token **current, bool *has_redirections, t_ctx *ctx)
{
	if ((*current)->next && handle_redirection_token(cmd, *current,
			(*current)->next, ctx) == -1)
		return (false);
	*has_redirections = true;
	if ((*current)->next)
		*current = (*current)->next;
	return (true);
}

/**
 * @brief Handles token processing based on token type
 *
 * @param cmd Current command being built
 * @param ctx Context containing environment information
 * @param args Arguments for this function
 * @return bool true on success, false on failure
 */
static bool	handle_token_by_type(t_command *cmd, t_ctx *ctx,
		t_handle_token args)
{
	bool	result;

	if ((*args.current)->type == TOK_WORD)
	{
		result = process_word_token_case(cmd, args.current, ctx,
				args.first_arg_processed);
		if (!result)
			return (false);
		if (*args.current && (*args.current)->type != TOK_WORD)
			return (true);
	}
	else if (token_is_redirection((*args.current)->type))
	{
		if (!process_redirection_token_case(cmd, args.current,
				args.has_redirections, ctx))
			return (false);
	}
	return (true);
}

/**
 * @brief Processes tokens until end of command or pipeline marker
 *
 * @param current Current token pointer reference
 * @param cmd Current command being built
 * @param ctx Context containing environment information
 * @return bool true on success, false on failure
 */
static bool	process_command_tokens(t_token **current, t_command *cmd,
		t_ctx *ctx)
{
	bool			first_arg_processed;
	bool			has_redirections;
	bool			result;
	t_handle_token	args;

	first_arg_processed = false;
	has_redirections = false;
	while (*current && (*current)->type != TOK_PIPE)
	{
		args = (t_handle_token){current, &first_arg_processed,
			&has_redirections};
		result = handle_token_by_type(cmd, ctx, args);
		if (!result)
			return (false);
		if (*current)
			*current = (*current)->next;
	}
	return (first_arg_processed || has_redirections);
}

/**
 * @brief Creates commands for a pipeline of commands
 *
 * @param cmd Current command pointer reference
 * @param current Current token pointer reference
 * @param ctx Context containing environment information
 * @return bool true on success, false on failure
 */
static bool	create_pipeline(t_command **cmd, t_token **current, t_ctx *ctx)
{
	t_command	*new_cmd;
	t_command	*prev_cmd;

	prev_cmd = *cmd;
	new_cmd = command_new();
	if (!new_cmd)
		return (false);
	prev_cmd->next = new_cmd;
	prev_cmd->operator = TOK_PIPE;
	*cmd = new_cmd;
	*current = (*current)->next;
	if (!process_command_tokens(current, *cmd, ctx))
	{
		prev_cmd->next = NULL;
		free_command(new_cmd);
		return (false);
	}
	if (*current && (*current)->type == TOK_PIPE)
		return (create_pipeline(cmd, current, ctx));
	return (true);
}

/**
 * @brief Parses tokens into a command structure
 *
 * @param ctx Context containing environment information
 * @param tokens The tokens array to parse
 * @return t_command* Parsed command structure or NULL if parsing fails
 */
t_command	*command_parse(t_ctx *ctx, t_token *tokens)
{
	t_command	*cmd;
	t_command	*first_cmd;
	t_token		*current;

	cmd = command_new();
	if (!cmd)
		return (NULL);
	first_cmd = cmd;
	current = tokens;
	if (!process_command_tokens(&current, cmd, ctx))
	{
		free_all_commands(first_cmd);
		return (NULL);
	}
	if (current && current->type == TOK_PIPE)
	{
		if (!create_pipeline(&cmd, &current, ctx))
		{
			free_all_commands(first_cmd);
			return (NULL);
		}
	}
	return (first_cmd);
}
