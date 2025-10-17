/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:04:32 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 14:09:00 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"

/**
 * @brief Handles standard environment variable expansion
 *
 * @param ctx Shell context
 * @param str Input string
 * @param i Current position (will be updated)
 * @return char* Expanded environment variable or empty string
 */
char	*expand_env_var(t_ctx *ctx, char *str, int *i)
{
	char	*var_name;
	char	*var_value;

	var_name = get_var_name(str, i);
	if (!var_name)
		return (ft_strdup(""));
	var_value = expand_var(ctx, var_name);
	free(var_name);
	return (var_value);
}

/**
 * @brief Handles basic special variables ($#, $?, $0)
 *
 * @param ctx Shell context
 * @param str Input string
 * @param i Current position (will be updated)
 * @return char* Expanded value or NULL if not a special variable
 */
static char	*handle_special_var(t_ctx *ctx, char *str, int *i)
{
	if (str[*i] == '#')
	{
		(*i)++;
		return (ft_strdup("0"));
	}
	else if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(ctx->exit_status));
	}
	else if (str[*i] == '0')
	{
		(*i)++;
		if (ctx->argv && ctx->argv[0])
			return (ft_strdup(ctx->argv[0]));
		return (ft_strdup("minishell"));
	}
	return (NULL);
}

/**
 * @brief Handles positional parameters and simple special vars
 *
 * @param str Input string
 * @param i Current position (will be updated)
 * @return char* Empty string for special vars, NULL if not special
 */
static char	*handle_positional_var(char *str, int *i)
{
	if ((str[*i] >= '1' && str[*i] <= '9') || str[*i] == '@' || str[*i] == '*'
		|| str[*i] == '!' || str[*i] == '$' || str[*i] == '^' || str[*i] == '%')
	{
		(*i)++;
		return (ft_strdup(""));
	}
	return (NULL);
}

/**
 * @brief Handles variable expansion based on quote context
 *
 * @param ctx Shell context
 * @param str Input string
 * @param i Current position (will be updated)
 * @return Expanded variable or dollar sign
 */
char	*expand_variable(t_ctx *ctx, char *str, int *i)
{
	char	*result;

	(*i)++;
	result = handle_special_var(ctx, str, i);
	if (result)
		return (result);
	result = handle_positional_var(str, i);
	if (result)
		return (result);
	if (!ft_isalpha(str[*i]) && str[*i] != '_')
		return (ft_strdup("$"));
	return (expand_env_var(ctx, str, i));
}
