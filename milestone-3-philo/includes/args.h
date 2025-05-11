/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 16:07:34 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 12:49:32 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
# define ARGS_H

# include "philo.h"

/**
 * @brief Checks if the arguments passed to the app are valid
 *
 * @param argc Arguments count
 * @param argv Arguments count
 * @return bool Whether valid or not
 */
bool	args(int argc, char **argv);

#endif
