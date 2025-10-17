/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find_bin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:40:56 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/08 16:53:31 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "path.h"

/**
 * @brief Retrieves PATH environment variable
 *
 * Searches through environment list for the PATH variable.
 *
 * @param ctx Shell context containing environment variables
 * @return PATH value or NULL if not found
 */
static char	*get_path_var(t_ctx *ctx)
{
	t_env	*env;

	env = ctx->env_list;
	while (env)
	{
		if (ft_strncmp(env->key, "PATH", 5) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/**
 * @brief Removes trailing slash from directory path if present
 *
 * Ensures directory paths are properly formatted for path joining.
 *
 * @param dir Directory path to normalize
 * @return Normalized path (modified in-place)
 */
static char	*normalize_dir_path(char *dir)
{
	int	len;

	len = (int)ft_strlen(dir);
	if (len > 0 && dir[len - 1] == '/')
		dir[len - 1] = '\0';
	return (dir);
}

/**
 * @brief Tries to find a binary in all PATH directories
 *
 * Searches for executable binary in each directory listed in PATH.
 *
 * @param path_dirs Array of directories from PATH
 * @param bin Binary name to search for
 * @return Full path if found, NULL otherwise
 */
static char	*search_in_path_dirs(char **path_dirs, char *bin)
{
	char	*path;
	int		i;

	i = 0;
	while (path_dirs[i])
	{
		path_dirs[i] = normalize_dir_path(path_dirs[i]);
		path = bin_find_path(path_dirs[i], bin);
		if (path)
			return (path);
		i++;
	}
	return (NULL);
}

/**
 * @brief Finds a binary in the PATH environment variable
 *
 * Splits PATH into directories and searches each one for the binary.
 *
 * @param ctx Shell context
 * @param bin Binary name to search for
 * @return Full path to binary if found and executable, NULL otherwise
 */
char	*env_find_bin(t_ctx *ctx, char *bin)
{
	char	*path_var;
	char	**path_dirs;
	char	*bin_path;

	if (!bin)
		return (NULL);
	path_var = get_path_var(ctx);
	if (!path_var || !*path_var)
		return (NULL);
	path_dirs = ft_split(path_var, ':');
	if (!path_dirs)
		return (NULL);
	bin_path = search_in_path_dirs(path_dirs, bin);
	free_2d_array((void **)path_dirs);
	return (bin_path);
}
