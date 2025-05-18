/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:09:47 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/18 13:13:37 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"
#include "mem.h"
#include "philo.h"

static void	wait_threads(t_ctx *ctx, pthread_t *big_brother)
{
	int	i;

	i = -1;
	while (++i < ctx->philos_count)
		pthread_join(ctx->philos[i].thread, NULL);
	pthread_join(*big_brother, NULL);
}

static void	final_coutdown(t_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->philos_count)
		pthread_mutex_destroy(&ctx->forks[i].mutex);
	pthread_mutex_destroy(&ctx->print_lock);
	pthread_mutex_destroy(&ctx->dead_lock);
	free_ctx(ctx);
}

/**
 * @brief Main entry to the ctx
 *
 * @param argc Arguments count
 * @param argv Arguments
 * @return int Return status
 */
int	main(int argc, char **argv)
{
	pthread_t	big_brother;
	t_ctx		*ctx;
	int			code;

	if (args(argc, argv))
		return (1);
	ctx = init_ctx(argc, argv);
	if (!ctx)
		return (EXIT_FAILURE);
	code = init_mutexes(ctx);
	if (code)
		return (code);
	init_philos(ctx);
	if (launch_philos(ctx))
		return (EXIT_FAILURE);
	if (launch_big_brother(ctx, &big_brother))
		return (EXIT_FAILURE);
	wait_threads(ctx, &big_brother);
	final_coutdown(ctx);
	return (EXIT_SUCCESS);
}
