/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_radix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:22:52 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/12 17:47:52 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static size_t   get_max_bits(const ssize_t max)
{
    size_t  max_bits;

    max_bits = 0;
    while ((max >> max_bits) != 0)
        max_bits++;
    return (max_bits);
}

/**
 * Complete implementation of the radix sort algorithm
 * @param   stack   Stack
 */
void    sort_radix(t_stack *stack_a)
{
    t_stack *stack_b;
    size_t  size;
    size_t  max_bits;
    size_t  i;
    size_t  j;
    ssize_t max;

    stack_b = NULL;
    size = stack_size(stack_a);
    max = stack_max(stack_a);
    max_bits = get_max_bits(max);
    for (i = 0; i < max_bits; i++)
    {
        for (j = 0; j < size; j++)
        {
            if ((stack_a->content >> i) & 1)
                ra(&stack_a);
            else
                pb(&stack_a, &stack_b);
        }
        while (stack_b)
            pa(&stack_a, &stack_b);
    }
}
