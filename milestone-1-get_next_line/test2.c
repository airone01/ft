/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:14:17 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/09 13:05:54 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	char	*line;
	int		fd;

    (void) argc;
//	 fd = open("test.txt", O_RDONLY);
//	 fd = open("1char.txt", O_RDONLY);
//	fd = open("bee-movie.txt", O_RDONLY);
    fd = open(argv[1], O_RDONLY);
	line = get_next_line(fd);
	printf("text: >%s<\n", line);
	free(line);
	// line = get_next_line(fd);
	// printf("text: >%s<\n", line);
	// free(line);
	return (0);
}
