/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 15:50:13 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/07 16:00:06 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include "get_next_line.h"

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int main(int argc, char **argv) {
	char    *line;
	int     fd;
	int     line_count = 0;

	if (argc != 2) {
		fprintf(stderr, "Usage: %s <test_content>\n", argv[0]);
		return 1;
	}

	// Create test file
	fd = open("test_input.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1) {
		fprintf(stderr, "Error creating test file\n");
		return 1;
	}
	write(fd, argv[1], strlen(argv[1]));
	close(fd);

	// Open file for reading
	fd = open("test_input.txt", O_RDONLY);
	if (fd == -1) {
		fprintf(stderr, "Error opening test file\n");
		return 1;
	}

	// Read lines until end of file
	while ((line = get_next_line(fd)) != NULL) {
		printf("%s", line);
		free(line);
		line_count++;
	}

	// Clean up
	close(fd);
	unlink("test_input.txt");

	return 0;
}
