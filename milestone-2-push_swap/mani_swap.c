/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mani_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:52:50 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/20 16:00:18 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	swap(t_stack *stack)
{
	ssize_t	tmp;

	if (!stack || !stack->next)
		return ;
	tmp = stack->val;
	stack->val = stack->next->val;
	stack->next->val = tmp;
	tmp = stack->idx;
	stack->idx = stack->next->idx;
	stack->next->idx = tmp;
}

/**
 * Swap the first 2 elements at the top of stack a.
 * Do nothing if there is only one or no elements.
 * @param   stack_a Stack A
 */
void	sa(t_stack *stack_a)
{
	swap(stack_a);
	write(1, "sa\n", 3);
}

/**
 * Swap the first 2 elements at the top of stack b.
 * Do nothing if there is only one or no elements.
 * @param   stack_b Stack B
 */
void	sb(t_stack *stack_b)
{
	swap(stack_b);
	write(1, "sb\n", 3);
}

/**
 * sa and sb at the same time.
 * @param   stack_a Stack A
 * @param   stack_b Stack B
 */
void	ss(t_stack *stack_a, t_stack *stack_b)
{
	swap(stack_a);
	swap(stack_b);
	write(1, "ss\n", 3);
}
