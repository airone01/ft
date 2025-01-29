/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:51:09 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/29 19:51:48 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Prints a command
 */
void	cmd_print(void *content)
{
	char	*cmd;

	cmd = (char *)content;
	ft_printf("bin:\t%s\n", (char *)cmd);
}
