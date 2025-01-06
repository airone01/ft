/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_pos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:55:15 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/06 18:10:55 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Assigns a position to every node of a stack from top to bottom in ascending
 * order. This is used to calculate the cost of moving a node to a certain pos.
 * @example With values 3 0 9 1 and indexes 3 1 4 2 and pos 0 1 2 3
 * @param   stack   Stack
 */
void	stack_pos(t_stack **stack)
{
	t_stack	*tmp;
	ssize_t	i;

	tmp = *stack;
	i = 0;
	while (tmp)
	{
		tmp->pos = i;
		tmp = tmp->next;
		i++;
	}
}

/**
 * Finds a target position between elements in stack A for element from stack B.
 * Looks for smallest index in A that's greater than B's index.
 * @param   stack_a     Stack A
 * @param   b_idx       Index of Stack B element
 * @return              Target position, or -1 if not found
 */
static ssize_t	find_between_target(t_stack **stack_a, ssize_t b_idx)
{
	t_stack	*tmp_a;
	ssize_t	target_idx;
	ssize_t	target_pos;

	tmp_a = *stack_a;
	target_idx = LONG_MAX;
	target_pos = 0;
	while (tmp_a)
	{
		if (tmp_a->idx > b_idx && tmp_a->idx < target_idx)
		{
			target_idx = tmp_a->idx;
			target_pos = tmp_a->pos;
		}
		tmp_a = tmp_a->next;
	}
	if (target_idx != LONG_MAX)
		return (target_pos);
	return (-1);
}

/**
 * Picks the best target in stack A for the given index of an element in stack B.
 * First tries to place B element between A elements by finding an A element with
 * bigger index. If not possible, finds element with smallest index in A.
 * @param   stack_a     Stack A
 * @param   b_idx       Index of Stack B element
 * @param   target_pos  Initial target position
 * @return              Final target position
 */
static ssize_t	stack_target(t_stack **stack_a, ssize_t b_idx,
		ssize_t target_pos)
{
	ssize_t	between_pos;
	t_stack	*tmp_a;
	ssize_t	target_idx;

	between_pos = find_between_target(stack_a, b_idx);
	if (between_pos != -1)
		return (between_pos);
	tmp_a = *stack_a;
	target_idx = LONG_MAX;
	while (tmp_a)
	{
		if (tmp_a->idx < target_idx)
		{
			target_idx = tmp_a->idx;
			target_pos = tmp_a->pos;
		}
		tmp_a = tmp_a->next;
	}
	return (target_pos);
}

void	stack_target_pos(t_stack **stack_a, t_stack **stack_b)
{
	t_stack	*tmp_b;
	ssize_t	target_pos;

	target_pos = 0;
	tmp_b = *stack_b;
	stack_pos(stack_a);
	stack_pos(stack_b);
	while (tmp_b)
	{
		target_pos = stack_target(stack_a, tmp_b->idx, target_pos);
		tmp_b->t_pos = target_pos;
		tmp_b = tmp_b->next;
	}
}
