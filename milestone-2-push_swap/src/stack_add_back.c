/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_add_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:09:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/16 16:15:40 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Appends a new number at the end of a stack
 * @param	stack	Stack
 * @param	nbr		Number to add
 */
void	stack_add_back(t_stack *stack, long nbr)
{
	t_stack	*last;
	t_stack	*tmp;

	if (!stack)
		return ;
	tmp = stack_new(nbr);
	if (!tmp)
		return ;
	last = stack_last(stack);
	last->next = tmp;
}
