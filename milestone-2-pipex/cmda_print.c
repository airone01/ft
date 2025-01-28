/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmda_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:51:09 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/28 20:04:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Prints a command
 */
void	cmda_print(void *content)
{
	t_cmda	*cmda;
	char	**args;

	if (!content)
	{
		ft_printf("[DEBUG] cmda_print: NULL content\n");
		return ;
	}
	cmda = (t_cmda *)content;
	ft_printf("[COMMAND (advanced)]\npath: '%s'\nargs: ", cmda->bin);
	args = cmda->args;
	while (*args)
	{
		ft_printf("'%s'", *args);
		if (*(args + 1))
			ft_printf(" ");
		args++;
	}
	ft_printf("\n");
}
