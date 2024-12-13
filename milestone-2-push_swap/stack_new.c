/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:04:50 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/12 16:41:29 by elagouch         ###   ########.fr       */
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
	head->content = nbr;
    head->next = NULL;
    head->prev = NULL;
	return (head);
}
