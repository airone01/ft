/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:09:47 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/26 16:45:49 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This file contains the main entrypoint of this philo implementation, and some
** utilities that go along with it.
*/

#include "philo.h"
#include <bits/types/struct_timeval.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>

static void	cleanup_mutexes(t_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->philos_count)
		pthread_mutex_destroy(&ctx->forks[i].mtx);
	pthread_mutex_destroy(&ctx->print_mtx);
	pthread_mutex_destroy(&ctx->ctx_mtx);
}

static void	wait_threads(t_ctx *ctx, pthread_t *big_brother, int philo_count)
{
	int	i;

	i = -1;
	while (++i < philo_count)
		pthread_join(ctx->philos[i].thread, NULL);
	if (big_brother)
		pthread_join(*big_brother, NULL);
}

/*
** We don't handle the result of mtx_set, but tbh we're quitting the app int
** this case so there really isn't anything we can do.
*/
static bool	launch_long_stuff(t_ctx *ctx, int *created_threads,
		pthread_t *big_brother)
{
	if (launch_philos(ctx, created_threads))
	{
		mx_sbool(&ctx->ctx_mtx, &ctx->stop, true);
		wait_threads(ctx, NULL, *created_threads);
		cleanup_mutexes(ctx);
		free_ctx(ctx);
		return (true);
	}
	if (launch_big_brother(ctx, big_brother))
	{
		mx_sbool(&ctx->ctx_mtx, &ctx->stop, true);
		wait_threads(ctx, big_brother, (int)ctx->philos_count);
		cleanup_mutexes(ctx);
		free_ctx(ctx);
		return (true);
	}
	return (false);
}

int	main(int argc, char **argv)
{
	pthread_t		big_brother;
	t_ctx			*ctx;
	int				created_threads;
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		write(STDERR_FILENO, "gettimeofday() error\n", 21);
		return (EXIT_FAILURE);
	}
	if (args(argc, argv))
		return (EXIT_FAILURE);
	ctx = init_ctx(argc, argv);
	if (!ctx || init_mutexes(ctx))
		return (EXIT_FAILURE);
	init_philos(ctx);
	created_threads = 0;
	if (launch_long_stuff(ctx, &created_threads, &big_brother))
		return (EXIT_FAILURE);
	wait_threads(ctx, &big_brother, (int)ctx->philos_count);
	cleanup_mutexes(ctx);
	free_ctx(ctx);
	return (EXIT_SUCCESS);
}
