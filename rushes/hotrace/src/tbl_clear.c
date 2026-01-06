/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbl_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:02:13 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/22 21:46:31 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

/**
 * @brief	Frees all the memory allocated for the table.
 *
 * IT'S THE FINAL COUNTDOWN! 🎵
 *
 * @param	tbl		Table to clear.
 */
void	final_countdown(t_list *tbl[TBL_SIZE])
{
	t_list	*tmp;
	t_list	*next;
	size_t	i;

	i = 0;
	while (i < TBL_SIZE)
	{
		tmp = tbl[i];
		while (tmp)
		{
			next = tmp->next;
			if (tmp->key)
				free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			free(tmp);
			tmp = next;
		}
		tbl[i] = NULL;
		i++;
	}
}
