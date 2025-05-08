/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 15:09:18 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/08 17:02:33 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "execute.h"

/**
 * @brief Finds the end of a variable name
 *
 * @param str String containing the variable
 * @param start Start position of the variable (after $)
 * @return End position of the variable name
 */
static int	find_var_end(char *str, int start)
{
	int	end;

	end = start + 1;
	while (str[end] && (ft_isalnum(str[end]) || str[end] == '_'))
		end++;
	return (end);
}

/**
 * @brief Processes a single environment variable in a string
 *
 * @param ctx Context containing environment info
 * @param result String being processed
 * @param var_start Pointer to the start of the variable ($ character)
 * @return Updated string with variable expanded or NULL on error
 */
static char	*process_one_variable(t_ctx *ctx, char *result, char *var_start)
{
	int		i;
	int		j;
	char	*var_name;
	char	*new_result;
	char	*replacement;

	i = (int)(var_start - result);
	j = find_var_end(result, i);
	var_name = extract_var_name(result, i, j);
	if (!var_name)
		return (result);
	replacement = get_env_value(ctx->env_list, var_name);
	free(var_name);
	if (!replacement)
		replacement = (char *)"";
	new_result = replace_substring(result, i, j, replacement);
	return (new_result);
}

/**
 * @brief Expands environment variables in a line
 *
 * @param ctx Context containing environment info
 * @param line Line to expand variables in
 * @return Newly allocated string with expanded variables
 */
char	*expand_variables_in_line(t_ctx *ctx, char *line)
{
	char	*result;
	char	*var_start;

	result = init_expansion(line);
	if (!result)
		return (NULL);
	var_start = ft_strchr(result, '$');
	while (var_start)
	{
		result = process_one_variable(ctx, result, var_start);
		if (!result)
			return (NULL);
		var_start = ft_strchr(result, '$');
	}
	return (result);
}
