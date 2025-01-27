/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_write.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 19:24:02 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/27 19:27:03 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Writes a file to a file descriptor
 */
void	file_write(int fd, char *file)
{
	if (write(fd, file, ft_strlen(file)) == -1)
		perror_and_exit();
	close(fd);
}
