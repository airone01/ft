/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mani_rrotate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 17:00:02 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/12 17:01:47 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void reverse_rotate(t_stack **stack)
{
    t_stack *last;
    t_stack *before_last;

    if (!*stack || !(*stack)->next)
        return ;
    last = stack_last(*stack);
    before_last = last->prev;
    before_last->next = NULL;
    last->prev = NULL;
    last->next = *stack;
    (*stack)->prev = last;
    *stack = last;
}

/**
 * Shift down all elements of stack a by 1.
 * The last element becomes the first one.
 * @param   stack_a Stack A
 */
void    rra(t_stack **stack_a)
{
    reverse_rotate(stack_a);
    ft_printf("rra\n");
}

/**
 * Shift down all elements of stack b by 1.
 * The last element becomes the first one.
 * @param   stack_b Stack B
 */
void    rrb(t_stack **stack_b)
{
    reverse_rotate(stack_b);
    ft_printf("rrb\n");
}

/**
 * rra and rrb at the same time.
 * @param   stack_a Stack A
 * @param   stack_b Stack B
 */
void    rrr(t_stack **stack_a, t_stack **stack_b)
{
    reverse_rotate(stack_a);
    reverse_rotate(stack_b);
    ft_printf("rrr\n");
}
