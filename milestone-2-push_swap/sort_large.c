/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_large.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 16:21:23 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/13 18:36:52 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void    sort_large(size_t len, t_stack **stack_a, t_stack **stack_b)
{
    push_save_three(len, stack_a, stack_b);
    sort_tiny(stack_a);
    while(stack_b)
    {
        stack_target_pos(stack_a, stack_b);
        cost((ssize_t)len, stack_a, stack_b);
    }
}
