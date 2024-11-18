/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:54:39 by elagouch          #+#    #+#             */
/*   Updated: 2024/10/02 10:50:28 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"

/*
 * Allocates a buffer and reads a file to it.
 *
 * @param	fname	path of the file
 * @param	fsize	number of bytes to read
 *
 * @returns	buffer with read data
 * @returns	null if error
 */
void	*ft_file_read(char *fname, int fsize)
{
	void	*buff;
	int		fd;

	fd = open(fname, O_RDONLY, 0);
	if (fd == -1)
		return (NULL);
	buff = malloc(fsize * sizeof(char) + 1);
	if (read(fd, buff, fsize) == -1)
	{
		free(buff);
		close(fd);
		return (NULL);
	}
	close(fd);
	((char *)buff)[fsize] = '\0';
	return (buff);
}

/*
 * Allocates a buffer and reads a file to it.
 *
 * @param	fsize	number of bytes to read
 *
 * @returns	buffer with read data
 * @returns	null if error
 */
void	*ft_stdin_read(int fsize)
{
	void	*buff;
	int		sread;

	buff = malloc(fsize * sizeof(char) + 1);
	sread = read(0, buff, fsize);
	if (sread == -1)
		return (free_and_null(buff));
	((char *)buff)[sread] = '\0';
	return (buff);
}
