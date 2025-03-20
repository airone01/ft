/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:09:27 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/22 16:43:57 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

/**
 * @brief	Displays an error message.
 *
 * @param	msg	The error message.
 * @param	err	The error code.
 */
void	error(char *msg, int err)
{
	(void)err;
	if (msg)
		ft_putendl_fd(msg, 2);
}
