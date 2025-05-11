/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:07:16 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 13:47:41 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "philo.h"

static void	init_ctx_atol(t_ctx *ctx, int argc, char **argv)
{
	unsigned long	tmp;

	ctx->philos_count = ft_atoul(argv[1]);
	tmp = ft_atoul(argv[2]);
	ctx->death_time = ULONG_MAX;
	if (!(tmp > ULONG_MAX / 1000))
		ctx->death_time = tmp * 1000;
	tmp = ft_atoul(argv[3]);
	ctx->meal_time = ULONG_MAX;
	if (!(tmp > ULONG_MAX / 1000))
		ctx->meal_time = tmp * 1000;
	tmp = ft_atoul(argv[4]);
	ctx->sleep_time = ULONG_MAX;
	if (!(tmp > ULONG_MAX / 1000))
		ctx->sleep_time = tmp * 1000;
	if (argc == 6)
		ctx->meals_count = ft_atoul(argv[5]);
}

static bool	init_ctx_check_zero(t_ctx *ctx, int argc)
{
	if (ctx->philos_count == 0 || ctx->death_time == 0 || ctx->meal_time == 0
		|| ctx->sleep_time == 0 || (argc == 6 && ctx->meals_count == 0))
	{
		printf("Error: All arguments except the meals count must be ");
		printf("greater than 0.\n");
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
	return (ctx);
}
