/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 11:33:27 by elagouch          #+#    #+#             */
/*   Updated: 2024/11/29 12:13:37 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RED "\033[1;31m"
#define GREEN "\033[1;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define RESET "\033[0m"

void	test_empty_file(void)
{
	int		fd;
	char	*line;

	printf("Empty file test: ");
	fd = open("empty.txt", O_RDWR | O_CREAT, 0644);
	line = get_next_line(fd);
	if (line == NULL)
		printf(GREEN "OK" RESET "\n");
	else
		printf(RED "KO" RESET "\n");
	close(fd);
}

void	test_single_line(void)
{
	int			fd;
	const char	*test_str = "This is a single line\n";
	char		*line;

	printf("Single line test: ");
	fd = open("single.txt", O_RDWR | O_CREAT, 0644);
	write(fd, test_str, strlen(test_str));
	close(fd);
	fd = open("single.txt", O_RDONLY);
	line = get_next_line(fd);
	if (line && strcmp(line, test_str) == 0)
		printf(GREEN "OK" RESET "\n");
	else
		printf(RED "KO" RESET "\n");
	free(line);
	close(fd);
}

void	test_multiple_lines(void)
{
	int			fd;
	const char	*test_str = "Line 1\nLine 2\nLine 3\n";
	char		*line;
	int			line_count;

	printf("Multiple lines test: ");
	fd = open("multiple.txt", O_RDWR | O_CREAT, 0644);
	write(fd, test_str, strlen(test_str));
	close(fd);
	fd = open("multiple.txt", O_RDONLY);
	line_count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		line_count++;
		free(line);
	}
	if (line_count == 3)
		printf(GREEN "OK" RESET "\n");
	else
		printf(RED "KO" RESET "\n");
	close(fd);
}

void	test_no_newline(void)
{
	int			fd;
	const char	*test_str = "This line has no newline";
	char		*line;

	printf("No newline test: ");
	fd = open("no_newline.txt", O_RDWR | O_CREAT, 0644);
	write(fd, test_str, strlen(test_str));
	close(fd);
	fd = open("no_newline.txt", O_RDONLY);
	line = get_next_line(fd);
	if (line && strcmp(line, test_str) == 0)
		printf(GREEN "OK" RESET "\n");
	else
		printf(RED "KO" RESET "\n");
	free(line);
	close(fd);
}

void	test_invalid_fd(void)
{
	char	*line;

	printf("Invalid FD test: ");
	line = get_next_line(-1);
	if (line == NULL)
		printf(GREEN "OK" RESET "\n");
	else
		printf(RED "KO" RESET "\n");
}

void	test_large_file(void)
{
	int			fd;
	char		*line;
	int			i;
	const char	*large_str = "This is a very long line that will be repeated many times to test buffer handling\n";

	printf("Large file test: ");
	fd = open("large.txt", O_RDWR | O_CREAT, 0644);
	for (i = 0; i < 1000; i++)
		write(fd, large_str, strlen(large_str));
	close(fd);
	fd = open("large.txt", O_RDONLY);
	i = 0;
	while ((line = get_next_line(fd)) != NULL && i < 1000)
	{
		i++;
		free(line);
	}
	if (i == 1000)
		printf(GREEN "OK" RESET "\n");
	else
		printf(RED "KO (%d lines read)" RESET "\n", i);
	close(fd);
}

void	test_mixed_line_lengths(void)
{
	int			fd;
	char		*line;
	const char	*test_str = "Short\nVery very very very very long line\n\nEmpty line above\n";

	printf("Mixed line lengths test:\n");
	fd = open("mixed.txt", O_RDWR | O_CREAT, 0644);
	write(fd, test_str, strlen(test_str));
	close(fd);
	fd = open("mixed.txt", O_RDONLY);
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("Read line: %s", line);
		free(line);
	}
	close(fd);
}

void	test_binary_data(void)
{
	int		fd;
	char	*line;
	char	binary_data[100];
	int		i;

	printf("Binary data test: ");
	fd = open("binary.txt", O_RDWR | O_CREAT, 0644);
	for (i = 0; i < 100; i++)
		binary_data[i] = i;
	write(fd, binary_data, 100);
	close(fd);
	fd = open("binary.txt", O_RDONLY);
	line = get_next_line(fd);
	if (line != NULL)
		printf(GREEN "OK" RESET "\n");
	else
		printf(RED "KO" RESET "\n");
	free(line);
	close(fd);
}

int	main(void)
{
	printf(YELLOW "=== Starting get_next_line tests ===\n\n" RESET);
	test_empty_file();
	test_single_line();
	test_multiple_lines();
	test_no_newline();
	test_invalid_fd();
	test_large_file();
	test_mixed_line_lengths();
	test_binary_data();
	printf(YELLOW "\n=== Tests completed ===\n" RESET);
	return (0);
}
