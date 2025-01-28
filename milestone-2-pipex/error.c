/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 18:17:07 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/28 15:57:52 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Print the error message and exit
 */
void	perror_and_exit(void)
{
	perror("Error");
	exit(errno);
}

/**
 * @brief	Set errno, print the error message and exit
 */
void	perror_errno_and_exit(size_t err)
{
	errno = err;
	perror_and_exit();
}
