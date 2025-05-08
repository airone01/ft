/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 10:56:03 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 14:24:11 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "free.h"

/**
 * @brief Initializes the environment in the context
 *
 * @param ctx Context
 * @param envp Environment
 */
static void	init_ctx_envp(t_ctx *ctx, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (!parse_env_var(envp[i], &ctx->env_list))
		{
			ctx_clear(ctx);
			return ;
		}
		i++;
	}
}

/**
 * @brief Initializes the context
 *
 * @param argc Arguments count
 * @param argv Arguments
 * @param envp Environment variables
 * @return t_ctx* Context
 */
t_ctx	*init_ctx(int argc, char **argv, char **envp)
{
	t_ctx	*ctx;

	ctx = malloc(sizeof(t_ctx));
	if (!ctx)
		exit(error(NULL, "malloc", ERR_ALLOC));
	ctx->env_list = NULL;
	init_ctx_envp(ctx, envp);
	ctx->exit_requested = false;
	ctx->exit_status = 0;
	ctx->quote.in_double_quote = 0;
	ctx->quote.in_single_quote = 0;
	ctx->tokens = NULL;
	ctx->cmd = NULL;
	ctx->argc = argc;
	ctx->argv = argv;
	ctx->envp = envp;
	ctx->fd_file_in = -1;
	ctx->fd_file_out = -1;
	return (ctx);
}

/**
 * @brief Creates a new environment variable node
 *
 * @param key Key of the environment variable
 * @param value Value of the environment variable
 * @return t_env* New environment variable node or NULL if allocation fails
 */
static t_env	*create_env_node(char *key, char *value)
{
	t_env	*new_node;

	new_node = (t_env *)malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->key = ft_strdup(key);
	if (!new_node->key)
	{
		free(new_node);
		return (NULL);
	}
	if (value)
	{
		new_node->value = ft_strdup(value);
		if (!new_node->value)
		{
			free(new_node->key);
			free(new_node);
			return (NULL);
		}
	}
	else
		new_node->value = NULL;
	new_node->next = NULL;
	return (new_node);
}

/**
 * @brief Adds an environment variable to the list
 *
 * @param env_list Pointer to the list head
 * @param key Key of the environment variable
 * @param value Value of the environment variable
 * @return int 1 if successful, 0 on error
 */
int	add_env_var(t_env **env_list, char *key, char *value)
{
	t_env	*new_node;
	t_env	*current;

	if (!key)
		return (0);
	new_node = create_env_node(key, value);
	if (!new_node)
		return (0);
	if (!*env_list)
	{
		*env_list = new_node;
		return (1);
	}
	current = *env_list;
	while (current->next)
		current = current->next;
	current->next = new_node;
	return (1);
}
