/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:17:48 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/20 18:36:31 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Deletes and frees a stack
 * @param   stack   Stack to completely delete
 */
void	stack_clear(t_stack *stack)
{
	t_stack *current;
	t_stack *next;

	current = stack;
	while (current)
	{
		next = current->next;
		stack_del_one(current);
		current = next;
	}
}
