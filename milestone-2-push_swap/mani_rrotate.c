/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mani_rrotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:00:02 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/16 16:12:07 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	reverse_rotate(t_stack **stack)
{
	t_stack	*last;
	t_stack	*pre_last;

	last = stack_last(*stack);
	pre_last = stack_before_last(*stack);
	if (pre_last)
		pre_last->next = NULL;
	last->next = *stack;
	*stack = last;
}

/**
 * Shift down all elements of stack a by 1.
 * The last element becomes the first one.
 * @param   stack_a Stack A
 */
void	rra(t_stack **stack_a, size_t display)
{
	reverse_rotate(stack_a);
	if (display)
		(void)!write(1, "rra\n", 4);
}

/**
 * Shift down all elements of stack b by 1.
 * The last element becomes the first one.
 * @param   stack_b Stack B
 */
void	rrb(t_stack **stack_b, size_t display)
{
	reverse_rotate(stack_b);
	if (display)
		(void)!write(1, "rrb\n", 4);
}

/**
 * rra and rrb at the same time.
 * @param   stack_a Stack A
 * @param   stack_b Stack B
 */
void	rrr(t_stack **stack_a, t_stack **stack_b, size_t display)
{
	reverse_rotate(stack_a);
	reverse_rotate(stack_b);
	if (display)
		(void)!write(1, "rrr\n", 4);
}
