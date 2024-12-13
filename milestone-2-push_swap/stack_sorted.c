/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_sorted.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:49:56 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/13 15:55:24 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Checks if a stack is sorted
 * @param   stack   Stack
 * @return          Whether the stack is sorted or not
 */
ssize_t stack_sorted(t_stack *stack)
{
    if (!stack->next)
        return (1);
    if (stack->val > stack->next->val)
        return (0);
    return (stack_sorted(stack->next));
}
