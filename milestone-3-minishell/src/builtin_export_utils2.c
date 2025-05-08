/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 17:05:56 by maximart          #+#    #+#             */
/*   Updated: 2025/05/06 15:05:07 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "error.h"
#include "init.h"  // for add_env_var
#include "lexer.h" // for t_parse

/**
 * @brief Extracts and validates the key and value from an export argument
 *
 * @param arg Argument to process (format key=value)
 * @param key_ptr Pointer to store the extracted key
 * @param value_ptr Pointer to store the extracted value
 * @param has_equals_ptr Pointer to indicate the presence of the equals sign
 * @return int 0 on success, 1 on error
 */
int	extract_export_data(char *arg, char **key_ptr, char **value_ptr,
		bool *has_equals_ptr)
{
	*key_ptr = get_env_key_from_export(arg);
	if (!*key_ptr)
		return (1);
	if (!validate_env_key(*key_ptr))
	{
		(void)error(arg, "export", ERR_IDENTIFIER);
		free(*key_ptr);
		*key_ptr = NULL;
		return (1);
	}
	*has_equals_ptr = (ft_strchr(arg, '=') != NULL);
	*value_ptr = NULL;
	if (*has_equals_ptr)
		*value_ptr = get_env_value_from_export(arg);
	return (0);
}

/**
 * @brief Updates or adds an environment variable
 *
 * @param ctx Context containing the environment
 * @param key Key to update
 * @param value Value to set
 * @param has_equals Indicates if the argument contained an equals sign
 * @return int 1 on success, 0 on failure
 */
int	update_or_add_env_var(t_ctx *ctx, char *key, char *value, bool has_equals)
{
	int	result;

	if (!update_env_var(&ctx->env_list, key, value, has_equals))
		result = add_env_var(&ctx->env_list, key, value);
	else
		result = 1;
	return (result);
}
