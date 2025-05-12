/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_lowest_pos.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 15:25:43 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/10 20:11:08 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Assigns a position to each element of a stack from top to bottom
 * @param	stack	Stack
 */
static void	get_position(t_stack **stack)
{
	t_stack	*tmp;
	long	i;

	i = 0;
	tmp = *stack;
	while (tmp)
	{
		tmp->pos = i;
		tmp = tmp->next;
		i++;
	}
}

long	stack_lowest_pos(t_stack **stack)
{
	t_stack	*tmp;
	long	lowest_index;
	long	lowest_pos;

	tmp = *stack;
	lowest_index = INT_MAX;
	get_position(stack);
	lowest_pos = tmp->pos;
	while (tmp)
	{
		if (tmp->idx < lowest_index)
		{
			lowest_index = tmp->idx;
			lowest_pos = tmp->pos;
		}
		tmp = tmp->next;
	}
	return (lowest_pos);
}
