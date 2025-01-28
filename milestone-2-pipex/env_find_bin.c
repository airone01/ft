/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find_bin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:40:56 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/28 16:13:50 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Gets directories from the PATH variable
 */
static char	**env_get_path_dirs(char **envp)
{
	char	*path_var;
	char	*path_value;
	char	**path_dirs;

	path_var = env_find(envp, "PATH=");
	if (!path_var)
		perror_errno_and_exit(ENOMEM);
	path_value = ft_strtrim(path_var, "PATH=");
	free(path_var);
	if (!path_value)
		perror_errno_and_exit(ENOMEM);
	path_dirs = ft_split(path_value, ':');
	free(path_value);
	if (!path_dirs)
		perror_errno_and_exit(ENOMEM);
	return (path_dirs);
}

/**
 * @brief	Frees an array of strings
 */
static void	free_strings(char **strings)
{
	char	**tmp;

	tmp = strings;
	while (*tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(strings);
}

/**
 * Finds a binary in the PATH variable or in the current directory
 *
 * @param env	The environment variables
 * @param bin	The binary to search for
 *
 * @returns		A full path to the binary if it is found and executable,
 * 				or NULL.
 *
 * @exception	ENOMEM if malloc fails
 */
char	*env_find_bin(char **envp, char *bin)
{
	char	**path_dirs;
	char	**og_path_dirs;
	char	*path;

	if (!envp || !bin)
		return (NULL);
	path_dirs = env_get_path_dirs(envp);
	og_path_dirs = path_dirs;
	while (*path_dirs)
	{
		path = path_find_bin(*path_dirs, bin);
		if (path)
			return (free_strings(og_path_dirs), path);
		path_dirs++;
	}
	free_strings(og_path_dirs);
	return (NULL);
}
