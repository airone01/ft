/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:17:07 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 02:14:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Exits the program safely with an error number
 */
void	app_exit_errno(t_ctx app, unsigned long errno_p)
{
	errno = (int)errno_p;
	app_exit(app);
}

/**
 * @brief	Exits the program safely
 */
void	app_exit(t_ctx app)
{
	app_free(app);
	perror("Error");
	exit(errno);
}
