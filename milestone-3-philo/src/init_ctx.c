/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:07:16 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/26 15:46:34 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include "std.h"
#include <unistd.h> // write, STDERR_FILENO

static void	*err_free_null(t_ctx *ctx)
{
	write(STDERR_FILENO, FG_RED ERR_COLON ERR_MALLC NC,
		ERR_LEN_BASE + ERR_LEN_MALLC);
	free_ctx(ctx);
	return (NULL);
}

static bool	init_ctx_check_zero(t_ctx *ctx, int argc)
{
	if (ctx->philos_count == 0 || (argc == 6 && ctx->max_meal_count == 0))
	{
		write(STDERR_FILENO, FG_RED ERR_COLON ERR_PHILC NC,
			ERR_LEN_BASE + ERR_LEN_PHILC);
		free_ctx(ctx);
		return (true);
	}
	return (false);
}

t_ctx	*init_ctx(int argc, char **argv)
{
	t_ctx	*ctx;

	ctx = ft_calloc(1, sizeof(t_ctx));
	if (!ctx)
	{
		write(STDERR_FILENO, FG_RED ERR_COLON ERR_MALLC NC,
			ERR_LEN_BASE + ERR_LEN_MALLC);
		return (NULL);
	}
	args_parse(ctx, argc, argv);
	if (init_ctx_check_zero(ctx, argc))
		return (NULL);
	ctx->forks = ft_calloc((size_t)ctx->philos_count, sizeof(t_fork));
	if (!ctx->forks)
		return (err_free_null(ctx));
	ctx->philos = ft_calloc((size_t)ctx->philos_count, sizeof(t_philo));
	if (!ctx->philos)
		return (err_free_null(ctx));
	return (ctx);
}
