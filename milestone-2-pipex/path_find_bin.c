/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_find_bin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:59:39 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/29 16:46:48 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Checks if a binary is found in a directory and is executable and returns the
 * allocated full path if it is, or NULL if it isn't
 *
 * @param dir	The path to search in
 * @param bin	The binary to search for
 *
 * @returns		A full path to the binary if it is found and executable,
 * 				or NULL.
 *
 * @exception	ENOMEM if malloc fails
 */
char	*path_find_bin(t_app *app, char *dir, char *bin)
{
	char	*tmp;
	char	*full_path;

	if (!dir || !bin)
		return (NULL);
	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		app_exit_errno(*app, ENOMEM);
	full_path = ft_strjoin(tmp, bin);
	free(tmp);
	if (!full_path)
		app_exit_errno(*app, ENOMEM);
	if (access(full_path, X_OK) == 0)
		return (full_path);
	free(full_path);
	return (NULL);
}
