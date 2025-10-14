/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:37:35 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/08 16:50:58 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if a character is valid for env variable name
 *
 * @param c Character to check
 * @return bool true if valid, false otherwise
 */
bool	is_valid_env_char(char c)
{
	return (ft_isalnum(c) || c == '_');
}

/**
 * @brief Gets the key part of an environment variable
 *
 * @param arg Argument string (key=value)
 * @return char* Key part (caller must free)
 */
char	*get_env_key_from_export(char *arg)
{
	char	*equals;
	char	*key;
	long	key_len;

	equals = ft_strchr(arg, '=');
	if (!equals)
		key_len = (long)ft_strlen(arg);
	else
		key_len = equals - arg;
	key = malloc((unsigned long)key_len + 1);
	if (!key)
		return (NULL);
	ft_strlcpy(key, arg, (unsigned long)key_len + 1);
	return (key);
}

/**
 * @brief Prints the environment in export format
 *
 * @param ctx Context for shell environment
 */
void	print_export_env(t_ctx *ctx)
{
	t_env	*env;

	env = ctx->env_list;
	while (env)
	{
		ft_printf("declare -x %s", env->key);
		if (env->value)
			ft_printf("=\"%s\"", env->value);
		ft_printf("\n");
		env = env->next;
	}
}

/**
 * @brief Updates an existing environment variable
 *
 * @param env_list Pointer to environment list
 * @param key Key to update
 * @param value New value
 * @param has_equals Whether the variable has an equals sign
 * @return bool true if updated, false if not found
 */
bool	update_env_var(t_env **env_list, char *key, char *value,
		bool has_equals)
{
	t_env	*current;

	current = *env_list;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			if (has_equals)
			{
				if (current->value)
					free(current->value);
				current->value = NULL;
				if (value)
					current->value = ft_strdup(value);
			}
			return (true);
		}
		current = current->next;
	}
	return (false);
}
