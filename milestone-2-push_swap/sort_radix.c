/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_radix.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:22:52 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/13 14:11:54 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Finds how many bits are needed to represent the largest normalized number
 * @param   num Largest normalized number
 * @return      Bit count
 */
static size_t   get_max_bits(const ssize_t num)
{
    size_t  max_bits;
    ssize_t max_num;

    max_bits = 0;
    max_num = num;
    while (max_num)
    {
        max_bits++;
        max_num >>= 1;
    }
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
    ssize_t min;
    ssize_t max;

    min = stack_min(stack_a);
    max = stack_max(stack_a);
    stack_b = NULL;
    size = stack_size(stack_a);
    max_bits = get_max_bits(max - min);
    for (i = 0; i < max_bits; i++)
    {
        for (j = 0; j < size; j++)
        {
            ssize_t normalized = stack_a->content - min;
            if ((normalized >> i) & 1)
                ra(&stack_a);
            else
                pb(&stack_a, &stack_b);
        }
        while (stack_b)
            pa(&stack_a, &stack_b);
    }
}
