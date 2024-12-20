/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:04:50 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/20 18:51:48 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
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
