/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmda_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:09:54 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/29 19:26:04 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * Frees an advanced command as a list of strings
 *
 * @param cmda	The advanced command
 */
void	cmda_free(void *cmda)
{
	char	**args;

	args = (char **)cmda;
	while (*args)
	{
		free(*args);
		args++;
	}
	free(cmda);
}
