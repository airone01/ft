/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_indexes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:10:32 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/16 16:16:14 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

/**
 * Assigns an index to each value of a stack
 * @param   stack   Stack
 * @param   len     Length of the stack
 * @returns			Truthy if entries were correct, falsy otherwise
 */
void	stack_indexes(t_stack *stack, size_t len)
{
	t_stack	*ptr;
	t_stack	*high;
	ssize_t	val;

	while (--len)
	{
		ptr = stack;
		val = LONG_MIN;
		high = NULL;
		while (ptr)
		{
			if (ptr->val == LONG_MIN && ptr->idx == 0)
				ptr->idx = 1;
			if (ptr->val > val && ptr->idx == 0)
			{
				val = ptr->val;
				high = ptr;
				ptr = stack;
			}
			else
				ptr = ptr->next;
		}
		if (high)
			high->idx = (ssize_t)len;
	}
}
