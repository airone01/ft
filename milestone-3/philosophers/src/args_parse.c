/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/05 10:01:48 by elagouch          #+#    #+#             */
/*   Updated: 2025/06/05 10:01:49 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** The goal of this file is to parse the cli arguments.
*/

#include "philo.h"
#include "std.h"

void	args_parse(t_ctx *ctx, int argc, char **argv)
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
