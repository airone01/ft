/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:04:50 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/06 20:05:27 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Generates a new stack object
 * @arg     nbr     Number of the head
 * @return  Stack
 */
t_stack	*stack_new(long nbr)
{
	t_stack	*head;

	head = ft_calloc(1, sizeof(t_stack));
	if (!head)
		return (NULL);
	head->val = nbr;
	head->next = NULL;
	head->idx = 0;
	head->pos = 0;
	head->t_pos = 0;
	head->cost_a = 0;
	head->cost_b = 0;
	return (head);
}