/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_push_save_three.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:22:30 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/20 13:24:14 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Pushes all the elements of Stack A into Stack B, except for the three last.
 * It pushes the lower values first for optimization reasons.
 * @param   len     Length of stack A
 * @param   stack_a Stack A
 * @param   stack_b Stack B
 */
void    push_save_three(t_stack **stack_a, t_stack **stack_b)
{
    size_t  pushed;
    size_t  len;
    size_t  i;

    i = 0;
    pushed = 0;
    len = stack_size(*stack_a);
    while (len > 6 && i < len && pushed < len / 2)
    {
        if ((*stack_a)->idx <= (ssize_t)len / 2)
        {
            pb(stack_a, stack_b);
            pushed++;
        }
        else
            ra(stack_a);
        i++;
    }
    while (len - pushed > 3)
    {
        pb(stack_a, stack_b);
        pushed++;
    }
}
