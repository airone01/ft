/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cheapest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:37:55 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/13 19:15:37 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <limits.h>

/**
 * Finds the node in stack B with the cheapest cost to move to stack A and
 * moves it the correct position in stack A.
 * @param   stack_a Stack A
 * @param   stack_b Stack B
 */
void    cheapest_move(t_stack **stack_a, t_stack **stack_b)
{
    t_stack *tmp;
    ssize_t cheap;
    ssize_t cost_a;
    ssize_t cost_b;

    tmp = *stack_b;
    cheap = LONG_MAX;
    while (tmp)
    {
        if (ft_abs(tmp->cost_a) + ft_abs(tmp->cost_b) < ft_abs(cheap))
        {
            cheap = ft_abs(tmp->cost_b) + ft_abs(tmp->cost_a);
            cost_a = tmp->cost_a;
            cost_b = tmp->cost_b;
        }
        tmp = tmp->next;
    }
    move(stack_a, stack_b, cost_a, cost_b);
}
