/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_find.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:13:07 by elagouch          #+#    #+#             */
/*   Updated: 2025/03/08 14:40:05 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Search for a variable in the environment and return a duplicate
 *
 * @param app The app structure
 * @param var The variable to search for
 * @return char* Environment variable content
 *
 * @note The searched variable *must* end with a '='
 */
char	*env_find(t_ctx *ctx, char *var)
{
	size_t	i;
	size_t	len;
	char	*env_var;

	if (!ctx->envp)
		return (NULL);
	i = 0;
	len = ft_strlen(var);
	while (ctx->envp[i])
	{
		if (ft_strncmp(ctx->envp[i], var, len) == 0)
		{
			env_var = ft_strdup(ctx->envp[i] + len);
			return (env_var);
		}
		i++;
	}
	return (NULL);
}
