/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:24:02 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/28 15:58:39 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Writes a file to a file descriptor
 */
void	file_write(ssize_t fd, char *file)
{
	if (write(fd, file, ft_strlen(file)) == -1)
		perror_and_exit();
	close(fd);
}
