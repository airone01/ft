/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_find_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:34:50 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:00:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

/**
 * @brief Checks if a path is a directory
 *
 * @param path Path to check
 * @return bool true if it's a directory, false otherwise
 */
bool	is_directory(const char *path)
{
	struct stat	path_stat;

	if (stat(path, &path_stat) != 0)
		return (false);
	return (S_ISDIR(path_stat.st_mode));
}

/**
 * @brief Resolves a relative path to an absolute one using current directory
 *
 * @param bin The path to resolve
 * @return char* New allocated absolute path or NULL on error
 */
static char	*resolve_relative_path(char *bin)
{
	char	*cwd;
	char	*absolute_path;
	char	*tmp;

	if (bin[0] == '/')
		return (ft_strdup(bin));
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (NULL);
	tmp = ft_strjoin(cwd, "/");
	free(cwd);
	if (!tmp)
		return (NULL);
	absolute_path = ft_strjoin(tmp, bin);
	free(tmp);
	return (absolute_path);
}

/**
 * @brief Checks and resolves a relative path binary
 *
 * @param bin Binary name to resolve
 * @param error_state Pointer to error state variable
 * @return char* Resolved path or NULL if not found/accessible
 */
char	*check_relative_path(char *bin, t_path_error *error_state)
{
	char	*path;

	if (bin[0] == '/' || *error_state != PATH_ERR_NONE)
		return (NULL);
	path = resolve_relative_path(bin);
	if (!path)
		return (NULL);
	if (access(path, X_OK) == 0)
		return (path);
	if (access(path, F_OK) == 0)
		*error_state = PATH_ERR_NO_PERMISSION;
	else if (is_directory(path))
		*error_state = PATH_ERR_IS_DIR;
	else
		*error_state = PATH_ERR_NOT_FOUND;
	free(path);
	return (NULL);
}

/**
 * @brief Displays appropriate error message based on error state
 *
 * @param bin Binary name that caused the error
 * @param error_state Current error state
 */
void	display_path_error(char *bin, t_path_error error_state)
{
	if (error_state == PATH_ERR_NOT_FOUND)
		exit(error(bin, NULL, ERR_NO_FILE));
	if (error_state == PATH_ERR_NO_PERMISSION)
		exit(error(bin, NULL, ERR_NO_PERMS));
	if (error_state == PATH_ERR_IS_DIR)
		exit(error(bin, NULL, ERR_IS_DIR));
}
