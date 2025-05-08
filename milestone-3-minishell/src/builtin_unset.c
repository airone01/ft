/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:56:32 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:00:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

/**
 * @brief Checks if a string is a valid environment variable name
 *
 * @param name String to check
 * @return bool true if valid, false otherwise
 */
static bool	is_valid_env_name(char *name)
{
	int	i;

	if (!name || !name[0])
		return (false);
	if (!ft_isalpha(name[0]) && name[0] != '_')
		return (false);
	i = 1;
	while (name[i])
	{
		if (!ft_isalnum(name[i]) && name[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Removes an environment variable from the list
 *
 * @param env_list Pointer to environment list
 * @param key Key to remove
 * @return bool true if removed, false if not found
 */
bool	remove_env_var(t_env **env_list, char *key)
{
	t_env	*current;
	t_env	*prev;

	if (!env_list || !*env_list || !key)
		return (false);
	current = *env_list;
	prev = NULL;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key) + 1) == 0)
		{
			if (prev)
				prev->next = current->next;
			else
				*env_list = current->next;
			free(current->key);
			if (current->value)
				free(current->value);
			free(current);
			return (true);
		}
		prev = current;
		current = current->next;
	}
	return (false);
}

/**
 * @brief Executes the unset built-in command
 *
 * @param ctx Context for shell environment
 * @param cmd Command containing arguments
 * @return int Exit status (0 for success, non-zero for error)
 */
int	builtin_unset(t_ctx *ctx, t_command *cmd)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (i <= cmd->arg_count)
	{
		if (!is_valid_env_name(cmd->args[i]))
		{
			(void)error(cmd->args[i], "unset", ERR_TOO_MANY_ARGS);
			status = 1;
		}
		else
			remove_env_var(&ctx->env_list, cmd->args[i]);
		i++;
	}
	return (status);
}
