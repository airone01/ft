/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 18:24:28 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/08 17:07:01 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "free.h"
#include "lexer.h" // for free_all_token

/**
 * @brief Closes any open file descriptors in the context
 *
 * @param ctx Context containing file descriptors
 */
static void	close_file_descriptors(t_ctx *ctx)
{
	if (ctx->fd_file_in != -1)
	{
		close(ctx->fd_file_in);
		ctx->fd_file_in = -1;
	}
	if (ctx->fd_file_out != -1)
	{
		close(ctx->fd_file_out);
		ctx->fd_file_out = -1;
	}
}

/**
 * @brief Frees environment, tokens and command structures from context
 *
 * @param ctx Context to clean up
 */
static void	free_structures(t_ctx *ctx)
{
	if (ctx->tokens)
	{
		free_all_token(ctx->tokens);
		ctx->tokens = NULL;
	}
	if (ctx->cmd)
	{
		free_all_commands(ctx->cmd);
		ctx->cmd = NULL;
	}
	if (ctx->env_list)
	{
		free_env_list(ctx->env_list);
		ctx->env_list = NULL;
	}
}

/**
 * @brief Clears the context and frees all allocated resources
 *
 * @param ctx context
 */
void	ctx_clear(t_ctx *ctx)
{
	if (!ctx)
		return ;
	free_structures(ctx);
	rl_clear_history();
	close_file_descriptors(ctx);
	free(ctx);
}
