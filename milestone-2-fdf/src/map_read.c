/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:51:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/19 12:33:21 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
// Helper Functions
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

/**
 * @brief Converts an array of string tokens to integer elevation values
 *
 * @param ctx Application context
 * @param tokens Array of string representations of numbers
 * @return int* Newly allocated array of integers
 */
static int	*convert_tokens_to_elevations(t_app *ctx, char **tokens)
{
	int	*elevations;
	int	i;

	elevations = safe_calloc(ctx, (unsigned long)ctx->map.width, sizeof(int));
	i = 0;
	while (i < ctx->map.width)
	{
		elevations[i] = ft_atoi(tokens[i]);
		i++;
	}
	return (elevations);
}

/**
 * @brief Validates and splits a map line into individual number tokens
 *
 * @param ctx Application context
 * @param raw_line Line read from map file
 * @return char** Array of number tokens (must be freed by caller)
 */
static char	**split_and_validate_line(t_app *ctx, char *raw_line)
{
	char	**tokens;
	int		token_count;

	tokens = ft_split(raw_line, ' ');
	if (!tokens || !tokens[0])
		exit_error_free(ctx, ERR_MAP_EMPTY_LINE, raw_line);
	token_count = 0;
	while (tokens[token_count])
		token_count++;
	if (ctx->map.width == 0)
		ctx->map.width = token_count;
	else if (token_count != ctx->map.width)
		exit_error_free(ctx, ERR_MAP_IRREGULAR, raw_line);
	return (tokens);
}

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
// Line Processing
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

/**
 * @brief Processes a single line from the map file
 *
 * @param ctx Application context
 * @param current_line Line to process (may be NULL for EOF)
 * @param row_index Pointer to current row index (will be incremented)
 * @return true Line was processed successfully
 * @return false End of file or termination condition reached
 */
static t_bool	process_map_line(t_app *ctx, char *current_line, int *row_index)
{
	char	**tokens;
	char	*clean_line;
	size_t	line_len;

	if (!current_line)
		return (false);
	line_len = ft_strlen(current_line);
	clean_line = ft_strtrim(current_line, "\n");
	free(current_line);
	if (!clean_line || !*clean_line)
	{
		free(clean_line);
		exit_error(ctx, ERR_MAP_EMPTY_LINE);
	}
	tokens = split_and_validate_line(ctx, clean_line);
	ctx->map.matrix[*row_index] = convert_tokens_to_elevations(ctx, tokens);
	free_2d_array((void **)tokens);
	free(clean_line);
	(*row_index)++;
	return (true);
}

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
// Main Map Reading Function
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

/**
 * @brief Reads and parses the map file into a height matrix
 *
 * @param ctx Application context
 * @param fd File descriptor of map file
 * @note Allocates memory for map matrix. Caller must ensure FD is valid.
 */
void	read_map_data(t_app *ctx, int fd)
{
	char	*raw_line;
	int		row_index;

	row_index = 0;
	while (true)
	{
		raw_line = get_next_line(fd);
		if (!process_map_line(ctx, raw_line, &row_index))
			break ;
		ctx->map.height = row_index;
		if (row_index >= MAX_MAP_HEIGHT)
			exit_error(ctx, ERR_MAP_TOO_LARGE);
		ctx->map.matrix = safe_recalloc(ctx, ctx->map.matrix,
				(unsigned long)(row_index - 1), (unsigned long)row_index);
		close(fd);
	}
}
