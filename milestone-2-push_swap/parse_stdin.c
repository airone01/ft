/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:10:11 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/11 17:42:31 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Whatever the stack, parses a number and adds it to it
 * @param   head    Head to add the new number to
 * @param   str     String to parse
 * @return          New stack head
 */
t_stack	*parse_and_add_anyway(t_stack *head, char *str)
{
	long	nbr;
	char	**strs;

	strs = ft_split(str, ' ');
	while (*strs)
	{
		nbr = ft_atoi(*strs);
		if (!head)
			head = stack_new(nbr);
		else
			stack_add_back(head, nbr);
		strs++;
	}
	return (head);
}

/**
 * Parses a stack from CLI argument(s)
 * @param   argc    Arguments count
 * @param   argv    Arguments
 * @return          Stack
 */
t_stack	*parse_stdin(int argc, char **argv)
{
	t_stack	*stack;

	argc--;
	stack = parse_and_add_anyway(NULL, *argv++);
	while (argc--)
		stack = parse_and_add_anyway(stack, *argv++);
	return (stack);
}
