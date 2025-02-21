/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_read.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 09:51:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/21 10:31:56 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/
// Helper Functions
/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

/**
 * @brief Converts an array of string tokens to integer elevation values
 *
 * @param ctx Application context
 * @param tokens Array of string representations of numbers
 *
 * @returns	int*	Newly allocated array of integers
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
 *
 * @returns	char**	Array of number tokens (must be freed by caller)
 */
static char	**split_and_validate_line(t_app *ctx, char *raw_line)
{
	char	**tokens;
	int		token_count;

	tokens = ft_split(raw_line, ' ');
	if (!tokens || !tokens[0])
	{
		free_2d_array((void **)tokens);
		exit_error_free(ctx, ERR_MAP_EMPTY_LINE, raw_line);
	}
	token_count = 0;
	while (tokens[token_count])
		token_count++;
	if (ctx->map.width == 0)
		ctx->map.width = token_count;
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
 *
 * @returns	t_bool	Whether the line was successfully processed
 */
static t_bool	process_map_line(t_app *ctx, char *current_line, int *row_index)
{
	char	**tokens;
	char	*clean_line;

	if (!current_line)
		return (false);
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
void	read_map_data(t_app *ctx)
{
	char	*raw_line;
	int		row_index;

	if (ctx->file_fd < 0)
		exit_error(ctx, ERR_FILE_OPEN);
	row_index = 0;
	while (true)
	{
		raw_line = get_next_line(ctx->file_fd);
		if (!process_map_line(ctx, raw_line, &row_index))
			break ;
	}
	close(ctx->file_fd);
}
