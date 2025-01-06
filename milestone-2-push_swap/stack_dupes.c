/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_dupes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 17:55:03 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/06 18:20:10 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Finds whether there are duplicates values in a stack
 * @param	s1	Stack
 * @return		Truthy if yes, otherwise falsy
 */
ssize_t stack_dupes(t_stack *s1)
{
	t_stack *start;
	t_stack *s2;

	if (!s1)
		return (0);
	stack_pos(&s1);
	start = s1;
	while (s1)
	{
		s2 = start;
		while (s2)
		{
			if ((s1->pos != s2->pos) && (s1->val == s2->val))
				return (1);
			s2 = s2->next;
		}
		s1 = s1->next;
	}
	return (0);
}
