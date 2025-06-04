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

static void	init_ctx_atol(t_ctx *ctx, int argc, char **argv)
{
	ctx->philos_count = (long)ft_atoul(argv[1]);
	ctx->death_time = (long)ft_atoul(argv[2]);
	ctx->meal_time = (long)ft_atoul(argv[3]);
	ctx->sleep_time = (long)ft_atoul(argv[4]);
	if (argc == 6)
		ctx->max_meal_count = (long)ft_atoul(argv[5]);
	else
		ctx->max_meal_count = -1;
	ctx->epoch = get_time(TIMEE_US);
}

static bool	init_ctx_check_zero(t_ctx *ctx, int argc)
{
	if (ctx->philos_count == 0 || (argc == 6 && ctx->max_meal_count == 0))
	{
		write(STDERR_FILENO,
			FG_RED "Error: Philos and meals counts arguments must be"
			" greater than 0.\n" NC,
			74);
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
		return (NULL);
	init_ctx_atol(ctx, argc, argv);
	if (init_ctx_check_zero(ctx, argc))
		return (NULL);
	ctx->forks = ft_calloc((size_t)ctx->philos_count, sizeof(t_fork));
	if (!ctx->forks)
	{
		free_ctx(ctx);
		return (NULL);
	}
	ctx->philos = ft_calloc((size_t)ctx->philos_count, sizeof(t_philo));
	if (!ctx->philos)
	{
		free_ctx(ctx);
		return (NULL);
	}
	return (ctx);
}
