/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:55:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:07:42 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "error.h"
#include "validation.h"

/**
 * @brief Validates environment variable name
 *
 * @param key Key to validate
 * @return bool true if valid, false otherwise
 */
bool	validate_env_key(char *key)
{
	int	i;

	if (!key || !key[0])
		return (false);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (false);
	i = 1;
	while (key[i])
	{
		if (!is_valid_env_char(key[i]))
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Gets the value part of an environment variable
 *
 * @param arg Export argument in form key=value
 * @return char* Value part (caller must free) or NULL if no value
 */
char	*get_env_value_from_export(char *arg)
{
	char	*equals;

	equals = ft_strchr(arg, '=');
	if (!equals)
		return (NULL);
	return (ft_strdup(equals + 1));
}

/**
 * @brief Processes a single export argument
 *
 * @param ctx Context containing environment
 * @param arg Argument to process
 * @return int 0 on success, 1 on error
 */
static int	process_export_arg(t_ctx *ctx, char *arg)
{
	char	*key;
	char	*value;
	bool	has_equals;
	int		result;

	key = NULL;
	value = NULL;
	if (extract_export_data(arg, &key, &value, &has_equals))
		return (1);
	result = update_or_add_env_var(ctx, key, value, has_equals);
	free(key);
	if (value)
		free(value);
	if (result)
		return (0);
	return (1);
}

/**
 * @brief Executes the export built-in command
 *
 * @param ctx Context for shell environment
 * @param cmd Command containing arguments
 * @return int Exit status (0 for success, non-zero for error)
 */
int	builtin_export(t_ctx *ctx, t_command *cmd)
{
	int	i;
	int	status;

	if (cmd->arg_count == 0)
	{
		print_export_env(ctx);
		return (0);
	}
	status = 0;
	i = 1;
	while (i <= cmd->arg_count)
	{
		if (process_export_arg(ctx, cmd->args[i]) != 0)
			status = 1;
		i++;
	}
	return (status);
}
