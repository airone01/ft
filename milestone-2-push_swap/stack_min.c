/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_min.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:56:05 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/13 16:41:38 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Gets the first node with the lowest value in a stack
 * @param   stack   Stack to search
 * @return          First node with the lowest value
 */
t_stack *stack_minn(t_stack *stack)
{
    t_stack *tmp;

    if (!stack->next)
        return (stack);
    tmp = stack_minn(stack->next);
    if (stack->val < tmp->val)
        return (stack);
    return (tmp);
}