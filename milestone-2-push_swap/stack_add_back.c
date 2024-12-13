/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_add_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:09:11 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/12 16:41:49 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Appends a new number at the end of a stack
 * @param stack
 * @param nbr
 */
void	stack_add_back(t_stack *stack, long nbr)
{
	t_stack	*last;
	t_stack	*tmp;

	if (!stack)
		return ;
	last = stack_last(stack);
	tmp = stack_new(nbr);
	if (!tmp)
		return ;
    tmp->prev = last;
	last->next = tmp;
}
