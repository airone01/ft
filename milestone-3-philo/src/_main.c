/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:09:47 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/26 11:39:14 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** This file contains the main entrypoint of this philo implementation, and some
** utilities that go along with it.
*/

#include "args.h"
#include "mem.h"
#include "philo.h"

static void	cleanup_mutexes(t_ctx *ctx)
{
	int	i;

	i = -1;
	while (++i < ctx->philos_count)
		pthread_mutex_destroy(&ctx->forks[i].mutex);
	pthread_mutex_destroy(&ctx->print_lock);
	pthread_mutex_destroy(&ctx->dead_lock);
	pthread_mutex_destroy(&ctx->start_mutex);
}

/*
** Join to wait on all the threads
*/
static void	wait_threads(t_ctx *ctx, pthread_t *big_brother)
{
	int	i;

	i = -1;
	while (++i < ctx->philos_count)
		pthread_join(ctx->philos[i].thread, NULL);
	pthread_join(*big_brother, NULL);
}

/*
** Clears at the end of the program
*/
static void	final_free(t_ctx *ctx)
{
	cleanup_mutexes(ctx);
	free_ctx(ctx);
}

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
		return (EXIT_FAILURE);
	init_philos(ctx);
	if (launch_philos(ctx))
	{
		cleanup_mutexes(ctx);
		free_ctx(ctx);
		return (EXIT_FAILURE);
	}
	if (launch_big_brother(ctx, &big_brother))
	{
		ctx->stop = true;
		wait_threads(ctx, &big_brother);
		final_free(ctx);
		return (EXIT_FAILURE);
	}
	wait_threads(ctx, &big_brother);
	final_free(ctx);
	return (EXIT_SUCCESS);
}
