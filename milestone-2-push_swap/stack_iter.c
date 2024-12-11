/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_iter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:02:30 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/11 17:43:18 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Calls a function iteratively on every stack layer
 * @param   stack   Stack
 * @param   f       Function
 */
void	stack_iter(t_stack *stack, void (*f)(t_stack *))
{
	f(stack);
	if (stack->next)
		stack_iter(stack->next, f);
}
