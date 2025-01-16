/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:17:48 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/06 17:50:35 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Deletes and frees a stack
 * @param   stack   Stack to completely delete
 */
void	stack_clear(t_stack *stack)
{
	t_stack	*current;
	t_stack	*next;

	if (!stack)
		return ;
	current = stack;
	while (current)
	{
		next = current->next;
		free(current);
		current = next;
	}
}