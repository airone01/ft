/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_cost.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:19:10 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/13 18:34:10 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void    cost(ssize_t len_a, t_stack **stack_a, t_stack **stack_b)
{
    t_stack *tmp_a;
    t_stack *tmp_b;
    ssize_t len_b;

    tmp_a = *stack_a;
    tmp_b = *stack_b;
    len_b = (ssize_t)stack_size(*stack_b);
    while (tmp_b)
    {
        tmp_b->cost_b = tmp_b->pos;
        if (tmp_b->pos > len_b / 2)
            tmp_b->cost_b = (len_b - tmp_b->pos) * -1;
        tmp_b->cost_a = tmp_b->t_pos;
        if (tmp_b->t_pos > len_a / 2)
            tmp_b->cost_a = (len_a - tmp_b->t_pos) * -1;
        tmp_b = tmp_b->next;
    }
}
