/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:39:38 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:00:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "validation.h"

/**
 * @brief Validates that the input string is not too long
 *
 * @param input The input string to validate
 * @param ctx Context for error handling
 * @return bool true if valid, false if invalid
 */
bool	validate_input_length(char *input, t_ctx *ctx)
{
	size_t	len;

	(void)ctx;
	if (!input)
		return (false);
	len = ft_strlen(input);
	if (len > MAX_INPUT_LEN)
	{
		(void)error(NULL, "validation", ERR_VLD_INPUT_LENGTH);
		return (false);
	}
	return (true);
}

static bool	is_valid_env_name(const char *name)
{
	if (!name || !name[0])
	{
		(void)error(NULL, "env", ERR_VLD_ENV_VAR_EMPTY);
		return (false);
	}
	if (!ft_isalpha(name[0]) && name[0] != '_')
	{
		(void)error(NULL, "env", ERR_VLD_ENV_VAR_START);
		return (false);
	}
	return (true);
}

/**
 * @brief Validates that an environment variable name is valid
 *
 * @param name The variable name to validate
 * @param ctx Context for error handling
 * @return bool true if valid, false if invalid
 */
bool	validate_env_var_name(char *name, t_ctx *ctx)
{
	int	i;

	(void)ctx;
	if (!is_valid_env_name(name))
		return (false);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
		{
			(void)error(NULL, "env", ERR_VLD_ENV_VAR_BAD_CHAR);
			return (false);
		}
		i++;
	}
	if (ft_strlen(name) > MAX_VAR_NAME_LEN)
	{
		(void)error(NULL, "env", ERR_VLD_ENV_VAR_TOO_LONG);
		return (false);
	}
	return (true);
}

/**
 * @brief Validates a filename for redirections
 *
 * @param filename The filename to validate
 * @param ctx Context for error handling
 * @return bool true if valid, false if invalid
 */
bool	validate_filename(char *filename, t_ctx *ctx)
{
	(void)ctx;
	if (!filename || !filename[0])
	{
		(void)error(NULL, "redir", ERR_VLD_REDIR_FILENAME_EMPTY);
		return (false);
	}
	if (ft_strlen(filename) > 255)
	{
		(void)error(NULL, "redir", ERR_VLD_REDIR_FILENAME_TOO_LONG);
		return (false);
	}
	return (true);
}

/**
 * @brief Validates a full command structure
 *
 * @param cmd The command to validate
 * @param ctx Context for error handling
 * @return bool true if valid, false if invalid
 */
bool	validate_command(t_command *cmd, t_ctx *ctx)
{
	t_redir	*redir;

	if (!cmd)
		return (false);
	redir = cmd->redirection;
	while (redir)
	{
		if (!validate_filename(redir->filename, ctx))
			return (false);
		redir = redir->next;
	}
	return (true);
}
