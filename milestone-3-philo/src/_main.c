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
#include <stdlib.h>   // EXIT_*
#include <sys/time.h> // gettimeofday()
#include <unistd.h>   // write()

static void	wait_threads(t_ctx *ctx, pthread_t *big_brother)
{
	int	i;

	i = -1;
	while (++i < ctx->philos_launched)
		pthread_join(ctx->philos[i].thread, NULL);
	if (big_brother)
		pthread_join(*big_brother, NULL);
}

/*
** We don't handle the result of mtx_set, but tbh we're quitting the app int
** this case so there really isn't anything we can do.
*/
static bool	launch_all_the_things(t_ctx *ctx, pthread_t *big_brother)
{
	if (launch_philos(ctx))
	{
		mx_sbool(&ctx->ctx_mtx, &ctx->stop, true);
		wait_threads(ctx, NULL);
		free_ctx(ctx);
		return (true);
	}
	if (launch_monitor(ctx, big_brother))
	{
		mx_sbool(&ctx->ctx_mtx, &ctx->stop, true);
		wait_threads(ctx, big_brother);
		free_ctx(ctx);
		return (true);
	}
	return (false);
}

/*
** True on error, false on none.
**
** Note: at this point in the program there us nothing to free yet.
** We can just exit.
*/
static bool	ensure_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		write(STDERR_FILENO, FG_RED ERR_GTIME NC, 37);
		return (true);
	}
	return (false);
}

int	main(int argc, char **argv)
{
	pthread_t		big_brother;
	t_ctx			*ctx;

	if (args_check(argc, argv)
		|| ensure_time())
		return (EXIT_FAILURE);
	ctx = init_ctx(argc, argv);
	if (!ctx
		|| init_mutexes(ctx)
		|| init_philos(ctx)
		|| launch_all_the_things(ctx, &big_brother))
		return (EXIT_FAILURE);
	wait_threads(ctx, &big_brother);
	free_ctx(ctx);
	return (EXIT_SUCCESS);
}
