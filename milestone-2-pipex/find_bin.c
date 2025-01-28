/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:56:48 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/28 17:58:15 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Finds a binary in the PATH variable or in the current directory
 *
 * @param envp	The environment variables
 * @param bin	The binary to search for
 *
 * @returns		A full path to the binary if it is found and executable,
 * 				or NULL.
 *
 * @exception	ENOMEM if malloc fails
 */
char	*find_bin(char **envp, char *bin)
{
	char	*result;

	if (!envp || !bin)
		return (NULL);
	result = path_find_bin("./", bin);
	if (result)
		return (result);
	result = env_find_bin(envp, bin);
	if (result)
		return (result);
	perror_errno_and_exit(ENOENT);
	return (NULL);
}
