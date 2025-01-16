/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_tiny.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:01:23 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/13 17:31:04 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Sorts a stack of 3 numbers in 2 or fewer moves.
 * @example For values 0 9 2 with indexes 1 3 2, the solution is two moves:
 * rra which makes it 2 0 9 with indexes 2 1 3 and then sa which makes it 0 2 9
 * with indexes 1 2 3.
 * @param   stack   Stack
 */
void	sort_tiny(t_stack **stack)
{
	ssize_t	high;

	if (stack_sorted(*stack))
		return ;
	high = stack_maxn(*stack)->idx;
	if ((*stack)->idx == high)
		ra(stack, 1);
	else if ((*stack)->next->idx == high)
		rra(stack, 1);
	if ((*stack)->idx > (*stack)->next->idx)
		sa(*stack, 1);
}