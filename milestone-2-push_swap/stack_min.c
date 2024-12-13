/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_min.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:56:05 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/13 14:10:37 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Gets the minimum content value in a stack
 * @param   stack   Stack to search
 * @return          Maximum number
 */
ssize_t stack_min(t_stack *stack)
{
    ssize_t tmp;

    if (!stack->next)
        return (stack->content);
    tmp = stack_min(stack->next);
    if (stack->content < tmp)
        return (stack->content);
    return (tmp);
}
