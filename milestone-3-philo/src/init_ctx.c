/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:07:16 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 18:42:07 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "philo.h"

static void	init_ctx_atol(t_ctx *ctx, int argc, char **argv)
{
	long	tmp;

	ctx->philos_count = (long)ft_atoul(argv[1]);
	tmp = (long)ft_atoul(argv[2]);
	if (tmp > LONG_MAX / 1000)
		ctx->death_time = LONG_MAX;
	else
		ctx->death_time = tmp * 1000;
	tmp = (long)ft_atoul(argv[3]);
	if (tmp > LONG_MAX / 1000)
		ctx->meal_time = LONG_MAX;
	else
		ctx->meal_time = tmp * 1000;
	tmp = (long)ft_atoul(argv[4]);
	if (tmp > LONG_MAX / 1000)
		ctx->sleep_time = LONG_MAX;
	else
		ctx->sleep_time = tmp * 1000;
	if (argc == 6)
		ctx->max_meal_count = (long)ft_atoul(argv[5]);
	else
		ctx->max_meal_count = -1;
	ctx->epoch = get_current_time();
}

static bool	init_ctx_check_zero(t_ctx *ctx, int argc)
{
	if (ctx->philos_count == 0 || ctx->death_time == 0 || ctx->meal_time == 0
		|| ctx->sleep_time == 0 || (argc == 6 && ctx->max_meal_count == 0))
	{
		printf("Error: All arguments must be greater than 0.\n");
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
	ctx->forks = ft_calloc((size_t)ctx->philos_count, sizeof(pthread_mutex_t));
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
	ctx->stop = false;
	return (ctx);
}
