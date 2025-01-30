/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find_bin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:40:56 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/30 16:56:06 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Gets directories from the PATH variable
 */
static char	**env_get_path_dirs(t_app *app)
{
	char	*path_var;
	char	*path_value;
	char	**path_dirs;

	path_var = env_find(*app, "PATH=");
	if (!path_var)
		app_exit_errno(*app, ENOMEM);
	path_value = ft_strtrim(path_var, "PATH=");
	free(path_var);
	if (!path_value)
		app_exit_errno(*app, ENOMEM);
	path_dirs = ft_split(path_value, ':');
	free(path_value);
	if (!path_dirs)
		app_exit_errno(*app, ENOMEM);
	return (path_dirs);
}

/**
 * Finds a binary in the PATH variable or in the current directory
 *
 * @param bin	The binary to search for
 *
 * @returns		A full path to the binary if it is found and executable,
 * 				or NULL.
 *
 * @exception	ENOMEM if malloc fails
 */
char	*env_find_bin(t_app *app, char *bin)
{
	char	**path_dirs;
	char	**og_path_dirs;
	char	*path;

	if (!bin)
		return (NULL);
	path_dirs = env_get_path_dirs(app);
	og_path_dirs = path_dirs;
	while (*path_dirs)
	{
		path = path_find_bin(app, *path_dirs, bin);
		if (path)
			return (free_strings(og_path_dirs), path);
		path_dirs++;
	}
	free_strings(og_path_dirs);
	return (NULL);
}
