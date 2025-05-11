/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:05:26 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 17:38:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEM_H
# define MEM_H

# include "philo.h"

/**
 * @brief Frees the context and returns a given return status
 *
 * @param ctx Context
 * @param code Return status
 * @return int Return status
 */
int		_rf(t_ctx *ctx, int status);

/**
 * @brief Frees the app context
 *
 * @param ctx Context
 */
void	free_ctx(t_ctx *ctx);

/**
 * @brief Initializes the context from the arguments
 *
 * @param argc Arguments count
 * @param argv Arguments
 * @return t_ctx* Context
 */
t_ctx	*init_ctx(int argc, char **argv);

/**
 * @brief Allocates the array for mutextes and initializes each mutex
 * @note In case of failure with any of the following errors, this function
 * frees what it has access to, so ctx with free_ctx and the mutextes with.
 * @throw EAGAIN, ENOMEM, EPERM, EINVAL
 * @see pthread_mutex_destroy(3)
 *
 * @param ctx Context
 * @return int 0 on success, any of the given error codes on failure
 */
int		init_mutexes(t_ctx *ctx);

/**
 * @brief Allocates the array for philosophers
 * @note The array is not NULL-terminated. Use ctx->philos_count
 *
 * @param ctx Context
 */
void	init_philos(t_ctx *ctx);

#endif
