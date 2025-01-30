/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_free_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:12:37 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/30 16:13:21 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Does absolutely nothing
 */
void	nothing(void *ptr)
{
	(void)ptr;
}

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
