/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_shift_back.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:35:10 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/13 16:49:37 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Assuming that most of the stack is sorted, this shifts the stack until its
 * lowest value is at the top.
 * If it is in the bottom half of the stack, the  function reverse rotates it
 * into position, otherwise rotates it until it's at the top of the stack.
 * @param   len     Length of stack
 * @param   stack   Stack
 */
void    stack_shift(ssize_t len, t_stack **stack)
{
    ssize_t low_idx;

    low_idx = stack_minn(*stack)->idx;
    if (low_idx > len / 2)
    {
        while (low_idx < len)
        {
            rra(stack);
            low_idx++;
        }
    }
    else
    {
        while (low_idx > 0)
        {
            ra(stack);
            low_idx--;
        }
    }
}
