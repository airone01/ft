/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 15:10:28 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/09 15:59:21 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include "ft_printf.h"
# include "libft.h"
# include <limits.h>

typedef struct s_ctx
{
	int	philos_count;
	int	death_time;
	int	meal_time;
	int	sleep_time;
	int	meals_count;
}		t_ctx;

#endif
