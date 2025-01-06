/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:47:32 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/06 14:16:37 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Reverse rotates both stack A and B until one of them is in position. The
 * given cost is negative since both positions are in the bottom half of their
 * respective stack. The cost is increased as the stacks are rotated, when one
 * reaches 0, the stack has been rotated as far as possible and the top
 * position is correct.
 * @param   stack_a Stack A
 * @param   stack_b Stack B
 * @param   cost_a  Cost of stack A
 * @param   cost_b  Cost of stack B
 */
static void	rrr_both(t_stack **stack_a, t_stack **stack_b, ssize_t *cost_a,
		ssize_t *cost_b)
{
	while (*cost_a < 0 && *cost_b < 0)
	{
		(*cost_a)++;
		(*cost_b)++;
		rrr(stack_a, stack_b);
	}
}

/**
 * Rotates both stack A and B until one of them is in position. The given cost
 * is positive since both positions are in the top half of their respective
 * stacks. The cost is decreased as the stacks are rotated, when one reaches 0
 * the stack has been rotated as far as possible and the top position is
 * correct.
 * @param   stack_a Stack A
 * @param   stack_b Stack B
 * @param   cost_a  Cost of stack A
 * @param   cost_b  Cost of stack B
 */
static void	rr_both(t_stack **stack_a, t_stack **stack_b, ssize_t *cost_a,
		ssize_t *cost_b)
{
	while (*cost_a > 0 && *cost_b > 0)
	{
		(*cost_a)--;
		(*cost_b)--;
		rr(stack_a, stack_b);
	}
}

/**
 * Rotates stack A until it is in position. If the cost is negative, teh stack
 * will be reversed, if it is positive, it will be rotated.
 * @param   stack_a Stack A
 * @param   cost    Cost of stack A
 */
static void	ra_both(t_stack **stack_a, ssize_t *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			ra(stack_a);
			(*cost)--;
		}
		else if (*cost < 0)
		{
			rra(stack_a);
			(*cost)++;
		}
	}
}

/**
 * Rotates stack A until it is in position. If the cost is negative, the stack
 * will be reversed, if it is positive, it will be rotated.
 * @param   stack_b Stack B
 * @param   cost    Cost of stack B
 */
static void	rb_both(t_stack **stack_b, ssize_t *cost)
{
	while (*cost)
	{
		if (*cost > 0)
		{
			rb(stack_b);
			(*cost)--;
		}
		else if (*cost < 0)
		{
			rrb(stack_b);
			(*cost)++;
		}
	}
}

/**
 * Chooses which move to make to get the B stack node to the correct
 * position in stack A. If the costs of moving stack A and B into position
 * match (i.e. both negative or both positive), both will be rotated or
 * reverse rotated at the same time. They might also be rotated separately,
 * before finally pushing the top B node to the top of stack A.
 * @param   stack_a Stack A
 * @param   stack_b Stack B
 * @param   cost_a  Cost of stack A
 * @param   cost_b  Cost of stack B
 */
void	move(t_stack **stack_a, t_stack **stack_b, ssize_t cost_a,
		ssize_t cost_b)
{
	if (cost_a < 0 && cost_b < 0)
		rrr_both(stack_a, stack_b, &cost_a, &cost_b);
	else
		rr_both(stack_a, stack_b, &cost_a, &cost_b);
	ra_both(stack_a, &cost_a);
	rb_both(stack_b, &cost_b);
	pa(stack_a, stack_b);
}
