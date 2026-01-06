/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmda_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:51:09 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/30 15:18:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Prints an advanced command, as an array of strings where the first
 * 			element is the binary path
 *
 * @param content	The advanced command
 */
void	cmda_print(void *content)
{
	char	**args;

	args = (char **)content;
	ft_printf("bin: %s\n", *args);
	args++;
	while (*args)
	{
		ft_printf("arg: %s\n", *args);
		args++;
	}
}
