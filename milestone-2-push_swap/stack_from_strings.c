/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_from_strings.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:15:04 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/11 17:42:37 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Builds a stack object from a pointer of strings and frees the strings.
 * @param   strings NULL-terminated pointer of strings
 * @return          Stack
 */
t_stack	*stack_from_strings(char **strings)
{
	t_stack	*head;
	long	nbr;

	head = NULL;
	nbr = ft_atol(*strings);
	if (!nbr)
		return (NULL);
	head = stack_new(nbr);
	strings++;
	while (*strings)
	{
		nbr = ft_atol(*strings);
		if (!nbr)
			return (stack_clear(head), NULL);
		head = stack_add_front(head, nbr);
		strings++;
	}
	return (head);
}
