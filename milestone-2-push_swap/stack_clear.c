/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:17:48 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/11 17:43:01 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Deletes and frees a stack
 * @param   stack   Stack to completely delete
 */
void	stack_clear(t_stack *stack)
{
	t_stack	*head;

	if (!stack)
		return ;
	head = stack->next;
	stack_del_one(stack);
	stack_clear(head);
}
