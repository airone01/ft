/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmda_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:52:18 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 02:14:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Splits the command into the arguments and finds the binary.
 * Then, it places the binary in the first argument.
 *
 * @param cmd	The command
 *
 * @returns		The command as an array of strings
 *
 * @exception	ENOMEM if malloc fails
 */
char	**cmda_args(t_ctx *app, char *cmd)
{
	char	**args;
	char	*bin_og;
	char	*bin;

	args = ft_split(cmd, ' ');
	if (!args)
		app_exit_errno(*app, ENOMEM);
	bin_og = args[0];
	bin = find_bin(app, bin_og);
	free(bin_og);
	args[0] = NULL;
	if (!bin)
	{
		free_strings(args);
		app_exit_errno(*app, ENOENT);
	}
	args[0] = bin;
	return (args);
}
