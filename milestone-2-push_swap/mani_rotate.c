/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mani_rotate.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:58:08 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/12 16:59:51 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void rotate(t_stack **stack)
{
    t_stack *last;
    t_stack *first;

    if (!*stack || !(*stack)->next)
        return ;
    first = *stack;
    last = stack_last(*stack);
    *stack = first->next;
    (*stack)->prev = NULL;
    first->next = NULL;
    first->prev = last;
    last->next = first;
}

/**
 * Shift up all elements of stack a by 1.
 * The first element becomes the last one.
 * @param   stack_a Stack A
 */
void    ra(t_stack **stack_a)
{
    rotate(stack_a);
    ft_printf("ra\n");
}

/**
 * Shift up all elements of stack B by 1.
 * The first element becomes the last one.
 * @param   stack_b Stack B
 */
void    rb(t_stack **stack_b)
{
    rotate(stack_b);
    ft_printf("rb\n");
}

/**
 * ra and rb at the same time
 * @param   stack_a Stack A
 * @param   stack_b Stack B
 */
void    rr(t_stack **stack_a, t_stack **stack_b)
{
    rotate(stack_a);
    rotate(stack_b);
    ft_printf("rr\n");
}
