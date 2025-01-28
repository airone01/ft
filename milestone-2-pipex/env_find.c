/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:07 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/28 14:27:07 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief Read the PATH variable from the environment
 *
 * Warning: The searched variable *must* end with a '='
 *
 * If PATH is not found, return NULL and don't error out,
 * as we can still search in the current directory
 */
char	*env_find(char **env, char *var)
{
	size_t	i;
	size_t	len;
	char	*path;

	i = 0;
	len = ft_strlen(var);
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0)
		{
			path = ft_strdup(env[i] + 5);
			return (path);
		}
		i++;
	}
	return (NULL);
}
