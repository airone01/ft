/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_quotes_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:07:40 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:07:35 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/**
 * @brief Handles context when in single quotes
 *
 * @param ctx Context containing quote information
 * @param i Current position (will be updated)
 * @return bool true to continue, false otherwise
 */
static bool	handle_single_quotes(t_ctx *ctx, int *i)
{
	if (ctx->quote.in_single_quote == 1 && ctx->quote.in_double_quote == 0)
	{
		(*i)++;
		return (true);
	}
	return (false);
}

/**
 * @brief Processes variable expansion in the string
 *
 * @param ctx Context containing variable information
 * @param str Input string
 * @param pos Position tracking struct
 * @param result Current result string
 * @return char* Updated result string or NULL on error
 */
static char	*process_variable(t_ctx *ctx, char *str, t_pos *pos, char *result)
{
	char	*updated_result;

	updated_result = append_text_part(pos->start, pos->current, result, str);
	if (!updated_result)
		return (NULL);
	updated_result = handle_var_expansion(ctx, str, &pos->current,
			updated_result);
	if (!updated_result)
		return (NULL);
	pos->start = pos->current;
	return (updated_result);
}

/**
 * @brief Iterates through the string and handles special characters
 *
 * @param ctx Context containing variable information
 * @param str String to process
 * @param result Current result string
 * @return char* Updated result string or NULL on error
 */
static char	*process_string_chars(t_ctx *ctx, char *str, char *result)
{
	t_pos	pos;
	char	*updated_result;

	pos.current = 0;
	pos.start = 0;
	updated_result = result;
	while (str[pos.current])
	{
		if (handle_single_quotes(ctx, &pos.current))
			continue ;
		if (str[pos.current] == '$')
		{
			updated_result = process_variable(ctx, str, &pos, updated_result);
			if (!updated_result)
				return (NULL);
			continue ;
		}
		pos.current++;
	}
	updated_result = append_text_part(pos.start, pos.current, updated_result,
			str);
	return (updated_result);
}

/**
 * @brief Processes a string, handling quotes and variable expansion
 *
 * @param ctx Context containing variable information
 * @param str String to process
 * @param result Current result string
 * @return Updated result string
 */
char	*process_string(t_ctx *ctx, char *str, char *result)
{
	return (process_string_chars(ctx, str, result));
}
