/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_count.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:20:21 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/12 17:52:21 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Counting sort implementation
 * @param   rdx     Radix
 * @param   stack   Stack
 * @param   dth     Index of digit. Can be refered to as `place`.
 */
void    sort_count(t_stack *stack, size_t dth)
{
    t_stack *output;
    size_t  count[10];
    t_stack *current;
    ssize_t index;
    size_t  i;

    current = stack;
    while (current)
    {
        index = (current->content / (ssize_t)dth) % 10;
        count[index]++;
        current = current->next;
    }
    for (i = 1; i < 10; i++)
        count[i] += count[i - 1];
    output = NULL;
    current = stack_last(stack);
    while (current)
    {
        index = (current->content / (ssize_t)dth) % 10;
        if (!output)
            output = stack_new(current->content);
        else
            stack_add_front(output, current->content);
        count[index]--;
        current = current->prev;
    }
    current = stack;
    while (output)
    {
        current->content = output->content;
        current = current->next;
        output = output->next;
    }
    stack_clear(output);
}
