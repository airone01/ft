/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 16:47:07 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:07:52 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "error.h"

/**
 * @brief Gets the old PWD directory from environment
 *
 * @param ctx Context for shell environment
 * @return char* Old PWD or NULL if not found
 */
char	*get_old_pwd(t_ctx *ctx)
{
	t_env	*env_node;

	env_node = ctx->env_list;
	while (env_node)
	{
		if (ft_strncmp(env_node->key, "OLDPWD", ft_strlen("OLDPWD") + 1) == 0)
			return (ft_strdup(env_node->value));
		env_node = env_node->next;
	}
	(void)error(NULL, "cd", ERR_NO_OLDPWD);
	return (NULL);
}

/**
 * @brief Gets the home directory from environment
 *
 * @param ctx Context for shell environment
 * @return char* Home directory or NULL if not found
 */
char	*get_home_dir(t_ctx *ctx)
{
	t_env	*env_node;

	env_node = ctx->env_list;
	while (env_node)
	{
		if (ft_strncmp(env_node->key, "HOME", ft_strlen("HOME") + 1) == 0)
			return (ft_strdup(env_node->value));
		env_node = env_node->next;
	}
	(void)error(NULL, "cd", ERR_NO_HOME);
	return (NULL);
}

/**
 * @brief Updates PWD environment variable
 *
 * @param env_node Current environment node
 * @param new_pwd New PWD value
 * @return t_env* Pointer to OLDPWD node if found, NULL otherwise
 */
t_env	*update_pwd_variable(t_env *env_node, char *new_pwd)
{
	t_env	*old_pwd_node;
	bool	pwd_found;

	old_pwd_node = NULL;
	pwd_found = false;
	while (env_node)
	{
		if (ft_strncmp(env_node->key, "PWD", ft_strlen("PWD") + 1) == 0)
		{
			free(env_node->value);
			env_node->value = new_pwd;
			pwd_found = true;
		}
		else if (ft_strncmp(env_node->key, "OLDPWD", ft_strlen("OLDPWD")
				+ 1) == 0)
			old_pwd_node = env_node;
		env_node = env_node->next;
	}
	if (!pwd_found)
		free(new_pwd);
	return (old_pwd_node);
}

/**
 * @brief Updates OLDPWD environment variable
 *
 * @param old_pwd_node OLDPWD environment node
 * @param old_pwd Old PWD value
 * @return void
 */
void	update_oldpwd_variable(t_env *old_pwd_node, char *old_pwd)
{
	if (old_pwd_node && old_pwd)
	{
		free(old_pwd_node->value);
		old_pwd_node->value = old_pwd;
	}
	else if (old_pwd)
		free(old_pwd);
}

/**
 * @brief Handles cd . when current directory doesn't exist
 *
 * @return char* Directory path or NULL if not found
 */
char	*handle_dot_directory(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd)
	{
		free(pwd);
		return (ft_strdup("."));
	}
	return (ft_strdup("."));
}
