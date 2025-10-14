/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_find.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:07 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 01:02:47 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// GPM? begin ft_env_find
char	*ft_env_find(char **envp, const char *var)
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
// GPM? end ft_env_find
