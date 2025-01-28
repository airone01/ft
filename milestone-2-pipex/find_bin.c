/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 14:56:48 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/28 16:01:24 by elagouch         ###   ########.fr       */
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
	char	*tmp;
	char	*clean_var;
	char	**paths;

	if (!envp || !bin)
		return (NULL);
	tmp = path_find_bin("./", bin);
	if (tmp)
		return (tmp);
	tmp = env_find_bin(envp, bin);
	if (tmp)
		return (tmp);
	perror_errno_and_exit(ENOENT);
	return (NULL);
}
