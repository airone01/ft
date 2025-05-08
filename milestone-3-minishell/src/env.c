/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 12:30:04 by maximart          #+#    #+#             */
/*   Updated: 2025/05/08 16:52:43 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

/**
 * @brief Process a part of a string and append it to the result
 *
 * @param result Current result string
 * @param str Input string
 * @param start Start position
 * @param end End position
 * @return Updated result string
 */
char	*append_part(char *result, char *str, int start, int end)
{
	char	*part;
	char	*new_result;

	if (end <= start)
		return (result);
	part = ft_substr(str, (unsigned int)start, (unsigned long)(end - start));
	if (!part)
		return (result);
	new_result = join_and_free(result, part);
	free(part);
	return (new_result);
}

/**
 * @brief Gets the value of an environment variable
 *
 * @param env_list Environment variable list
 * @param key Key to look for
 * @return Value of the variable or NULL if not found
 */
char	*get_env_value(t_env *env_list, char *key)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strncmp(current->key, key, ft_strlen(key)) == 0
			&& ft_strlen(current->key) == ft_strlen(key))
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

/**
 * @brief Expands a variable name to its value
 *
 * @param ctx Context containing the current shell state
 * @param var_name Name of the variable to expand
 * @return char* Expanded value as a new string (caller must free)
 */
char	*expand_var(t_ctx *ctx, char *var_name)
{
	char	*value;

	if (!var_name)
		return (ft_strdup(""));
	if (ft_strncmp(var_name, "?", ft_strlen(var_name)) == 0)
		return (ft_itoa(ctx->exit_status));
	value = get_env_value(ctx->env_list, var_name);
	if (value)
		return (ft_strdup(value));
	return (ft_strdup(""));
}

/**
 * @brief Gets a variable name from a string
 *
 * @param str String containing the variable
 * @param pos Position in the string (will be updated)
 * @return Newly allocated string with variable name or NULL
 */
char	*get_var_name(char *str, int *pos)
{
	char	*name;
	int		len;
	int		i;

	i = *pos;
	if (str[i] == '?')
	{
		(*pos)++;
		return (ft_strdup("?"));
	}
	len = 0;
	while (str[i + len] && (ft_isalnum(str[i + len]) || str[i + len] == '_'))
		len++;
	if (len == 0)
		return (NULL);
	name = malloc((unsigned long)(len + 1));
	if (!name)
		return (NULL);
	ft_strlcpy(name, str + i, (unsigned long)(len + 1));
	*pos += len;
	return (name);
}

/**
 * @brief Handles special variable expansion (exit status, $#, $0)
 *
 * @param ctx Shell context
 * @param str Input string
 * @param i Current position (will be updated)
 * @return char* Expanded value for special variables
 */
char	*expand_special_var(t_ctx *ctx, char *str, int *i)
{
	(*i)++;
	if (str[*i] == '?')
	{
		(*i)++;
		return (ft_itoa(ctx->exit_status));
	}
	if (str[*i] == '#')
	{
		(*i)++;
		return (ft_strdup("0"));
	}
	if (str[*i] == '0')
	{
		(*i)++;
		if (ctx->argv && ctx->argv[0])
			return (ft_strdup(ctx->argv[0]));
		return (ft_strdup("minishell"));
	}
	return (NULL);
}
