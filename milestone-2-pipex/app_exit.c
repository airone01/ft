/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:17:07 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/10 19:50:08 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Exits the program safely with an error number
 */
void	app_exit_errno(t_app app, unsigned long errno_p)
{
	errno = (int)errno_p;
	app_exit(app);
}

/**
 * @brief	Exits the program safely
 */
void	app_exit(t_app app)
{
	app_free(app);
	perror("Error");
	exit(errno);
}
