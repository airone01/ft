/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_2d_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 16:38:09 by elagouch          #+#    #+#             */
/*   Updated: 2025/03/08 15:07:04 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees a NULL-terminated pointer of pointers
 *
 * @param ptrs The pointer of pointers to free
 */
void	free_2d_array(void **ptrs)
{
	int	i;

	if (!ptrs)
		return ;
	i = 0;
	while (ptrs[i])
	{
		free(ptrs[i]);
		i++;
	}
	free(ptrs);
}
