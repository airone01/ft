/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_last.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:02:28 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/11 17:43:23 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Gets the last element in a stack recursively.
 * Will always return an element, except if stack is NULL.
 * @param   stack   Stack
 * @return          Last stack element
 */
t_stack	*stack_last(t_stack *stack)
{
	if (!stack)
		return (NULL);
	if (stack->next)
		return (stack_last(stack->next));
	return (stack);
}
