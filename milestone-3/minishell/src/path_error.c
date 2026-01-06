/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:37:57 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 14:27:24 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

/**
 * @brief Gets appropriate error code for path resolution failures
 *
 * @param err_type Type of error encountered
 * @return int Error code (127 for not found, 126 for permission, etc.)
 */
int	get_path_error_code(t_error_type err_type)
{
	if (err_type == ERR_NO_FILE || err_type == ERR_CMD_NOT_FOUND)
		return (127);
	if (err_type == ERR_NO_PERMS || err_type == ERR_IS_DIR)
		return (126);
	return (1);
}

/**
 * @brief Handles path-related errors: prints message and returns code.
 *
 * @param path Path that caused the error
 * @param err_type Type of error encountered
 * @return int Error code for shell exit status
 */
int	handle_path_error(char *path, t_error_type err_type)
{
	return (error(path, NULL, err_type));
}
