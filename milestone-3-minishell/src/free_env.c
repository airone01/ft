/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 14:42:24 by maximart          #+#    #+#             */
/*   Updated: 2025/05/06 14:23:38 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "init.h"

/**
 * @brief Frees environment variable list
 *
 * @param env_list List to free
 */
void	free_env_list(t_env *env_list)
{
	t_env	*current;
	t_env	*next;

	current = env_list;
	while (current)
	{
		next = current->next;
		free(current->key);
		if (current->value)
			free(current->value);
		free(current);
		current = next;
	}
}

/**
 * @brief Parses an environment variable string
 *
 * @param env_str Environment variable string (KEY=VALUE)
 * @param env_list Pointer to the environment list
 * @return 1 if successful, 0 on error
 */
int	parse_env_var(char *env_str, t_env **env_list)
{
	char	*equals_pos;
	char	*key;
	char	*value;
	int		key_len;
	int		result;

	equals_pos = ft_strchr(env_str, '=');
	if (!equals_pos)
		return (add_env_var(env_list, env_str, NULL));
	key_len = (int)(equals_pos - env_str);
	key = (char *)malloc((size_t)(key_len + 1));
	if (!key)
		return (0);
	ft_strlcpy(key, env_str, (size_t)(key_len + 1));
	value = equals_pos + 1;
	result = add_env_var(env_list, key, value);
	free(key);
	return (result);
}
