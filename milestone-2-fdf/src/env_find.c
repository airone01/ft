/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:07 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/13 00:42:49 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/**
 * Search for a variable in the environment
 *
 * @param envp	The environment to search in
 * @param var	The variable to search for
 *
 * Warning: The searched variable *must* end with a '='
 *
 * If the variable is not found, return NULL and don't error out.
 */
char	*env_find(char **envp, const char *var)
{
	unsigned long	len;
	unsigned long	i;
	char			*path;

	i = 0;
	len = ft_strlen(var);
	while (envp[i])
	{
		if (ft_strncmp(envp[i], var, len) == 0)
		{
			path = ft_strdup(envp[i] + len);
			return (path);
		}
		i++;
	}
	return (NULL);
}
