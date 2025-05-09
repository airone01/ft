/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:09:47 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/09 17:57:38 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "args.h"
#include "mem.h"
#include "philo.h"

static void	cycle_of_life(t_ctx *ctx, t_philo *philos)
{
	pthread_t	monitor;
	int			status;

	status = 0;
	launch_philos(ctx, philos);
	pthread_create(&monitor, NULL, death_check, NULL);
	waitpid(-1, &status, 0);
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
