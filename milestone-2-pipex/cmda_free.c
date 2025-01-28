/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmda_free.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 19:09:54 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/28 20:08:10 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmda_free(void *cmda)
{
	char	**args;

	args = ((t_cmda *)cmda)->args;
	while (*args)
	{
		free(*args);
		args++;
	}
	free(((t_cmda *)cmda)->args);
	free(((t_cmda *)cmda)->bin);
	free(cmda);
}
