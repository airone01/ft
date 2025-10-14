/* ************************************************************************** */
/*                                                                            */
/*                                                        :::     ::::::::   */
/*   env_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 17:55:13 by maximart          #+#    #+#             */
/*   Updated: 2025/03/24 11:32:12 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "lexer.h"

/**
 * @brief Handles expanding variables during string processing
 *
 * @param ctx Context containing environment information
 * @param str Input string
 * @param i Position in string (will be updated)
 * @param result Current result string
 * @return Updated result string
 */
char	*handle_var_expansion(t_ctx *ctx, char *str, int *i, char *result)
{
	char	*var_value;
	char	dollar[2];

	dollar[0] = '$';
	dollar[1] = '\0';
	if (ctx->quote.in_single_quote == 1 && ctx->quote.in_double_quote == 0)
	{
		result = join_and_free(result, dollar);
		(*i)++;
		return (result);
	}
	var_value = expand_variable(ctx, str, i);
	if (!var_value)
		return (result);
	result = join_and_free(result, var_value);
	free(var_value);
	return (result);
}

char	*append_text_part(int start, int i, char *result, char *str)
{
	char	*temp_result;

	if (i > start)
	{
		temp_result = append_part(result, str, start, i);
		if (!temp_result)
			return (NULL);
		result = temp_result;
		return (result);
	}
	return (result);
}

/**
 * @brief Handles quotes and variables in a string
 *
 * @param ctx Context containing variable information
 * @param str Input string to process
 * @return Newly allocated string with processed content
 */
char	*handle_quotes_and_vars(t_ctx *ctx, t_token *token)
{
	char	*result;
	char	*processed;

	if (token->quote.in_single_quote)
		return (ft_strdup(token->value));
	if (!token->value)
		return (ft_strdup(""));
	result = ft_strdup("");
	if (!result)
		return (NULL);
	processed = process_string(ctx, token->value, result);
	if (!processed)
	{
		free(result);
		return (ft_strdup(""));
	}
	return (processed);
}
