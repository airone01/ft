/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_find_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:59:39 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:00:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a file is executable
 *
 * Verifies that a file exists, is not a directory, and has execute permissions.
 *
 * @param path Path to the file to check
 * @return true if file is executable, false otherwise
 */
static bool	is_executable_file(const char *path)
{
	struct stat	path_stat;

	if (access(path, F_OK) != 0)
		return (false);
	if (stat(path, &path_stat) != 0)
		return (false);
	if (S_ISDIR(path_stat.st_mode))
		return (false);
	if (access(path, X_OK) != 0)
		return (false);
	return (true);
}

/**
 * @brief Creates a full path by joining directory and filename
 *
 * Allocates and constructs a path in the format "dir/bin".
 *
 * @param dir Directory path
 * @param bin Binary name
 * @return Newly allocated full path or NULL on allocation failure
 */
static char	*join_path(const char *dir, char *bin)
{
	char	*tmp;
	char	*full_path;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, bin);
	free(tmp);
	return (full_path);
}

/**
 * @brief Searches for a binary in a specific directory
 *
 * Checks if the specified binary exists and is executable in the given
 * directory.
 *
 * @param dir Directory to search in
 * @param bin Binary name to look for
 * @return Full path if executable binary found, NULL otherwise
 */
char	*bin_find_path(const char *dir, char *bin)
{
	char	*full_path;

	if (!dir || !bin)
		return (NULL);
	full_path = join_path(dir, bin);
	if (!full_path)
		return (NULL);
	if (is_executable_file(full_path))
		return (full_path);
	free(full_path);
	return (NULL);
}
