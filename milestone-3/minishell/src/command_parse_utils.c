/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parse_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:27:42 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/08 16:51:29 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/**
 * @brief Creates a new arguments array for the first command argument
 *
 * @param expanded_value The value to set as the first argument
 * @return char** Newly allocated args array or NULL on failure
 */
static char	**create_first_arg(char *expanded_value)
{
	char	**new_args;

	new_args = malloc(sizeof(char *) * 2);
	if (!new_args)
		return (NULL);
	new_args[0] = expanded_value;
	new_args[1] = NULL;
	return (new_args);
}

/**
 * @brief Creates and populates a new arguments array with additional slot
 *
 * @param cmd Command structure containing current args
 * @param expanded_value New value to add to args array
 * @return char** New args array or NULL on failure
 */
static char	**create_extended_args(t_command *cmd, char *expanded_value)
{
	char	**new_args;
	int		i;

	new_args = malloc(sizeof(char *) * ((unsigned long)cmd->arg_count + 3));
	if (!new_args)
		return (NULL);
	i = 0;
	while (i <= cmd->arg_count)
	{
		new_args[i] = cmd->args[i];
		i++;
	}
	new_args[i] = expanded_value;
	new_args[i + 1] = NULL;
	return (new_args);
}

/**
 * @brief Handles the case when args array is not yet initialized
 *
 * @param cmd Command structure being built
 * @param expanded_value Expanded token value to add
 * @return bool true on success, false on failure
 */
bool	handle_first_arg(t_command *cmd, char *expanded_value)
{
	char	**new_args;

	new_args = create_first_arg(expanded_value);
	if (!new_args)
	{
		free(expanded_value);
		return (false);
	}
	cmd->args = new_args;
	cmd->arg_count = 0;
	return (true);
}

/**
 * @brief Adds a new argument to an existing args array
 *
 * @param cmd Command structure being built
 * @param expanded_value Expanded token value to add
 * @return bool true on success, false on failure
 */
bool	add_to_existing_args(t_command *cmd, char *expanded_value)
{
	char	**new_args;

	new_args = create_extended_args(cmd, expanded_value);
	if (!new_args)
	{
		free(expanded_value);
		return (false);
	}
	free(cmd->args);
	cmd->args = new_args;
	cmd->arg_count++;
	return (true);
}

/**
 * @brief Processes a word token during command parsing
 *
 * @param cmd Command structure being built
 * @param token Current token being processed
 * @param ctx Context containing environment information
 * @return bool true on success, false on failure
 */
bool	process_word_token(t_command *cmd, t_token *token, t_ctx *ctx)
{
	char	*expanded_value;

	expanded_value = handle_quotes_and_vars(ctx, token);
	if (!expanded_value)
		return (false);
	if (!cmd->args)
		return (handle_first_arg(cmd, expanded_value));
	return (add_to_existing_args(cmd, expanded_value));
}
