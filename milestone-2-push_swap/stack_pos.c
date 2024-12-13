/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_pos.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:55:15 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/13 18:15:37 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Assigns a position to every node of a stack from top to bottom in ascending
 * order. This is used to calculate the cost of moving a node to a certain pos.
 * @example With values 3 0 9 1 and indexes 3 1 4 2 and pos 0 1 2 3
 * @param   stack   Stack
 */
static void stack_pos(t_stack **stack)
{
    t_stack *tmp;
    ssize_t i;

    tmp = *stack;
    i = 0;
    while(tmp)
    {
        tmp->pos = i;
        tmp = tmp->next;
        i++;
    }
}

/**
 * Picks the best target in stack A for the given index of an element in stack B.
 * Firstly checks if the index of the B element can be placed somewhere in
 * between elements in stack A, by checking whether there is an element in stack
 * A with a bigger index. If not, it finds the element with the smallest index
 * in A and assigns that as the position.
 * @param   stack_a     Stack A
 * @param   b_idx       Index of Stack B
 * @param   target_idx  Targeted index
 * @param   target_pos  Targeted position
 * @return              The target position
 */
static ssize_t  stack_target(t_stack **stack_a, ssize_t b_idx,
        ssize_t target_idx, ssize_t target_pos)
{
    t_stack *tmp_a;

    tmp_a = *stack_a;
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
    tmp_a = *stack_a;
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

void    stack_target_pos(t_stack **stack_a, t_stack **stack_b)
{
    t_stack *tmp_b;
    ssize_t target_pos;

    target_pos = 0;
    tmp_b = *stack_b;
    stack_pos(stack_a);
    stack_pos(stack_b);
    while (tmp_b)
    {
        target_pos = stack_target(stack_a, tmp_b->idx, LONG_MAX, target_pos);
        tmp_b->t_pos = target_pos;
        tmp_b = tmp_b->next;
    }
}
