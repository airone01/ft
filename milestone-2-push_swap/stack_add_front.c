/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_add_front.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:28:25 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/11 17:42:52 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Appends a new number at the head of a stack
 * @param stack
 * @param nbr
 */
t_stack	*stack_add_front(t_stack *stack, long nbr)
{
	t_stack	*tmp;

	if (!stack)
		return (NULL);
	tmp = stack_new(nbr);
	if (!tmp)
		return (NULL);
	tmp->next = stack;
	return (tmp);
}
