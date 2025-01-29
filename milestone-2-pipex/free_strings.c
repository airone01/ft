/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_strings.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:09:52 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/29 16:59:34 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Frees an array of strings
 */
void	free_strings(char **strings)
{
	char	**tmp;

	tmp = strings;
	while (tmp && *tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(strings);
}
