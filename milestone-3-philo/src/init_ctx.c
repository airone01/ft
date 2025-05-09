/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_ctx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:07:16 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/09 17:32:33 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mem.h"
#include "philo.h"

t_ctx	*init_ctx(int argc, char **argv)
{
	t_ctx	*ctx;

	ctx = ft_calloc(1, sizeof(t_ctx));
	ctx->philos_count = (unsigned long)ft_atoi(argv[1]);
	ctx->death_time = (unsigned long)ft_atoi(argv[2]);
	ctx->meal_time = (unsigned long)ft_atoi(argv[3]);
	ctx->sleep_time = (unsigned long)ft_atoi(argv[4]);
	if (argc == 6)
		ctx->meals_count = (unsigned long)ft_atoi(argv[5]);
	if ((int)ctx->philos_count <= 0 || (int)ctx->death_time <= 0
		|| (int)ctx->meal_time <= 0 || (int)ctx->sleep_time <= 0
		|| (int)ctx->meals_count < 0)
	{
		ft_printf_fd(STDERR_FILENO,
			"Error: All arguments except the meals count must be"
			"greater than 0.\n");
		free_ctx(ctx);
		return (NULL);
	}
	return (ctx);
}
