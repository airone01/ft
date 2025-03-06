/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:06:51 by elagouch          #+#    #+#             */
/*   Updated: 2025/03/06 10:12:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Creates an absolute path when a relative path is provided
 *
 * @param path The input path to resolve
 * @param envp Environment variables
 * @return char* The resolved path (must be freed by caller)
 */
static char	*resolve_path(char *path, char **envp)
{
	char	*cwd;
	char	*tmp;

	if (*path == '/')
		return (ft_strdup(path));
	cwd = ft_env_find(envp, "PWD=");
	if (!cwd)
		return (ft_strdup(path));
	if (cwd[ft_strlen(cwd) - 1] != '/')
	{
		tmp = ft_strjoin(cwd, "/");
		free(cwd);
		if (!tmp)
			return (NULL);
		cwd = tmp;
	}
	tmp = ft_strjoin(cwd, path);
	free(cwd);
	return (tmp);
}

/**
 * @brief Figure out file path, open a file and check for errors
 *
 * @param path The name of the file to open
 * @param envp Environment variables
 * @return int File descriptor or exits on error
 */
int	file_open(char *path, char **envp)
{
	int		fd;
	char	*resolved_path;

	if (!path || !*path)
		exit_error(NULL, ERR_ARG_INVALID_FILE);
	resolved_path = resolve_path(path, envp);
	if (!resolved_path)
		exit_error(NULL, ERR_MALLOC);
	fd = open(resolved_path, O_RDONLY);
	free(resolved_path);
	if (fd < 0)
		exit_error(NULL, ERR_FILE_OPEN);
	return (fd);
}
