/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_max.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:56:05 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/13 16:08:28 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Gets the first node with the highest value in a stack
 * @param   stack   Stack to search
 * @return          First node with the highest value
 */
t_stack *stack_maxn(t_stack *stack)
{
    t_stack *tmp;

    if (!stack->next)
        return (stack);
    tmp = stack_maxn(stack->next);
    if (stack->val > tmp->val)
        return (stack);
    return (tmp);
}