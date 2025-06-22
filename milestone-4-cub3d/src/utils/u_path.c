/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u_path.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 13:37:43 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/18 13:41:46 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include "utils.h"
#include <unistd.h>

static char	*get_directory_path(const char *filepath)
{
	char	*last_slash;
	char	*dir_path;
	int		dir_len;

	if (!filepath)
		return (NULL);
	last_slash = ft_strrchr(filepath, '/');
	if (!last_slash)
		return (ft_strdup("./"));
	dir_len = last_slash - filepath + 1;
	dir_path = ft_substr(filepath, 0, dir_len);
	return (dir_path);
}

static char	*join_paths(const char *dir_path, const char *rel_path)
{
	char	*temp;
	char	*result;

	if (!dir_path || !rel_path)
		return (NULL);
	temp = ft_strjoin(dir_path, rel_path);
	if (!temp)
		return (NULL);
	result = ft_strdup(temp);
	free(temp);
	return (result);
}

char	*resolve_path(const char *base_path, const char *relative_path)
{
	char	*dir_path;
	char	*resolved_path;

	if (!base_path || !relative_path)
		return (NULL);
	if (relative_path[0] == '/')
		return (ft_strdup(relative_path));
	dir_path = get_directory_path(base_path);
	if (!dir_path)
		return (NULL);
	resolved_path = join_paths(dir_path, relative_path);
	free(dir_path);
	return (resolved_path);
}
