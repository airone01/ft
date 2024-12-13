/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_max.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:56:05 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/12 16:01:44 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Gets the maximum content value in a stack
 * @param   stack   Stack to search
 * @return          Maximum number
 */
ssize_t stack_max(t_stack *stack)
{
    ssize_t tmp;

    if (!stack->next)
        return (stack->content);
    tmp = stack_max(stack->next);
    if (stack->content > tmp)
        return (stack->content);
    return (tmp);
}
