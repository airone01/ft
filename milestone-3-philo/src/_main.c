/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:09:47 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/09 18:42:53 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"
#include "mem.h"
#include "philo.h"

static void	cycle_of_life(t_ctx *ctx, t_philo *philos)
{
	pthread_t	monitor;
	int			i;

	launch_philos(ctx, philos);
	pthread_create(&monitor, NULL, (void *(*)(void *))death_check, philos);
	pthread_join(monitor, NULL);
	i = 0;
	while (i < (int)ctx->philos_count)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

/**
 * @brief Main entry to the program
 *
 * @param argc Arguments count
 * @param argv Arguments
 * @return int Return status
 */
int	main(int argc, char **argv)
{
	int		code;
	t_ctx	*ctx;
	t_philo	*philos;

	if (args(argc, argv))
		return (1);
	ctx = init_ctx(argc, argv);
	if (!ctx)
		return (EXIT_FAILURE);
	philos = init_philos(ctx);
	code = init_mutexes(ctx);
	if (code)
		return (code);
	gettimeofday(&ctx->epoch, NULL);
	cycle_of_life(ctx, philos);
	free_philos(philos);
	free_ctx(ctx);
	return (EXIT_SUCCESS);
}
