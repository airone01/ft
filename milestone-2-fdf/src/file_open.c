/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_open.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 22:06:51 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/13 00:43:06 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

static char	*resolve_path(char *path, char **envp)
{
	char	*cwd;
	char	*tmp;

	if (*path == '/')
		return (ft_strdup(path));
	cwd = env_find(envp, "PWD=");
	if (cwd)
	{
		if (cwd[ft_strlen(cwd) - 1] != '/')
		{
			tmp = ft_strjoin(cwd, "/");
			free(cwd);
			cwd = tmp;
		}
		tmp = ft_strjoin(cwd, path);
		free(cwd);
		return (tmp);
	}
	return (ft_strdup(path));
}

/**
 * @brief Figure out file path, open a file and check for errors
 *
 * @param filename	The name of the file to open
 */
int	file_open(char *path, char **envp)
{
	int	fd;

	if (!path || !*path)
		exit_error(NULL, ERR_ARG_INVALID_FILE);
	path = resolve_path(path, envp);
	if (!path)
		exit_error(NULL, ERR_MALLOC);
	fd = open(path, O_RDONLY);
	free(path);
	if (fd < 0)
		exit_error(NULL, ERR_FILE_OPEN);
	return (fd);
}
