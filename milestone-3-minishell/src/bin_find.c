/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:56:48 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:08:49 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "error.h"
#include "path.h"

/**
 * @brief Checks if a string contains path components
 *
 * Determines if the given string contains directory path components such as
 * slashes or relative path indicators ('.' or '..').
 *
 * @param str String to check for path components
 * @return true if the string contains path components, false otherwise
 */
bool	is_path(const char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (false);
	if (str[0] == '/' || str[0] == '~' || str[0] == '.' || str[0] == '\0')
		return (true);
	while (str[i])
	{
		if (str[i] == '/')
			return (true);
		i++;
	}
	return (false);
}

/**
 * @brief Validates and resolves an absolute or relative path
 *
 * Checks if the path exists, has proper permissions, and is not a directory.
 * Returns appropriate error status if validation fails.
 *
 * @param bin Path to validate
 * @param error_state Pointer to store error state
 * @return Duplicated path if valid, NULL otherwise
 */
static char	*validate_path(char *bin, t_path_error *error_state)
{
	if (is_directory(bin))
	{
		*error_state = PATH_ERR_IS_DIR;
		return (NULL);
	}
	if (access(bin, F_OK) != 0)
	{
		*error_state = PATH_ERR_NOT_FOUND;
		return (NULL);
	}
	if (access(bin, X_OK) != 0)
	{
		*error_state = PATH_ERR_NO_PERMISSION;
		return (NULL);
	}
	return (ft_strdup(bin));
}

/**
 * @brief Maps t_path_error to t_error_type for the error function.
 */
static t_error_type	map_path_error_to_type(t_path_error error_state)
{
	if (error_state == PATH_ERR_NOT_FOUND)
		return (ERR_NO_FILE);
	if (error_state == PATH_ERR_NO_PERMISSION)
		return (ERR_NO_PERMS);
	if (error_state == PATH_ERR_IS_DIR)
		return (ERR_IS_DIR);
	return (ERR_CMD_NOT_FOUND);
}

/**
 * @brief Resolves a command path, sets ctx->exit_status on error, returns NULL.
 *
 * Checks if the command is a path or a simple command and resolves it.
 * For paths, validates directly; for simple commands, searches in PATH.
 * Prints error messages via error() which also returns the code.
 *
 * @param ctx Shell context (used to store exit status on error)
 * @param bin Command to resolve
 * @return Resolved path (caller must free) or NULL on error.
 */
char	*bin_find(t_ctx *ctx, char *bin)
{
	char			*path;
	t_path_error	error_state;

	error_state = PATH_ERR_NONE;
	if (!bin || bin[0] == '\0')
	{
		ctx->exit_status = error("", NULL, ERR_CMD_NOT_FOUND);
		return (NULL);
	}
	if (is_path(bin))
	{
		path = validate_path(bin, &error_state);
		if (!path)
		{
			ctx->exit_status = handle_path_error(bin,
					map_path_error_to_type(error_state));
			return (NULL);
		}
		return (path);
	}
	path = env_find_bin(ctx, bin);
	if (!path)
		return (ctx->exit_status = error(bin, NULL, ERR_CMD_NOT_FOUND), NULL);
	return (path);
}
