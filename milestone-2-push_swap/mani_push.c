/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mani_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 16:56:18 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/16 16:12:20 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push(t_stack **dest, t_stack **src)
{
	t_stack	*tmp;

	if (!*src)
		return ;
	tmp = *src;
	*src = (*src)->next;
	tmp->next = *dest;
	*dest = tmp;
}

/**
 * Take the first element at the top of b and put it at the top of a.
 * Do nothing if b is empty.
 * @param   stack_a Stack A
 * @param   stack_b Stack B
 */
void	pa(t_stack **stack_a, t_stack **stack_b, size_t display)
{
	push(stack_a, stack_b);
	if (display)
		(void)!write(1, "pa\n", 3);
}

/**
 * Take the first element at the top of b and put it at the top of b.
 * Do nothing if a is empty.
 * @param   stack_a Stack A
 * @param   stack_b Stack B
 */
void	pb(t_stack **stack_a, t_stack **stack_b, size_t display)
{
	push(stack_b, stack_a);
	if (display)
		(void)!write(1, "pb\n", 3);
}
