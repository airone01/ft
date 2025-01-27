/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_legit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:00:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/16 16:16:24 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Tests a stack against the project requirements
 * @param	stack	Stack
 * @returns			0 on legit, else 1
 */
int	stack_legit(t_stack *stack)
{
	ssize_t	size;

	if (!stack)
		return (stack_clear_error(stack), 1);
	size = stack_size(stack);
	if (size < 1)
		return (stack_clear_error(stack), 1);
	if (size <= 1)
		return (stack_clear(stack), 1);
	stack_pos(&stack);
	if (stack_dupes(stack))
		return (stack_clear_error(stack), 1);
	return (0);
}
