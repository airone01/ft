/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq_map_size.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 13:34:24 by elagouch          #+#    #+#             */
/*   Updated: 2024/10/02 10:54:12 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"

/*
 * Counts the bytes of a file.
 *
 * @param	fd		file descriptor
 * @param	buff	buffer to read to
 *
 * @returns	amount of readable bytes
 */
int	bsq_handle_size(int fd, void *buff)
{
	int	size;
	int	count;

	count = 0;
	size = 100;
	while (size == 100)
	{
		size = read(fd, buff, 100);
		if (size == -1)
		{
			free(buff);
			close(fd);
			return (-1);
		}
		count += size;
	}
	return (count);
}

/*
 * Gets the length of the given entry file.
 *
 * @param	fname	the file name
 *
 * @returns	the number of bytes
 * @returns -1 if the file is unreadable
 */
int	bsq_map_file_size(char *fname)
{
	void	*buff;
	int		count;
	int		fd;

	fd = open(fname, O_RDONLY, 0);
	if (fd == -1)
		return (-1);
	buff = malloc(100 * sizeof(char));
	count = bsq_handle_size(fd, buff);
	if (count == -1)
		return (-1);
	free(buff);
	close(fd);
	return (count);
}
