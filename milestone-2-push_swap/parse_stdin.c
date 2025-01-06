/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_stdin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:10:11 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/06 17:32:54 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	strs_clear(char **strs)
{
	char	**ptr;

	if (!strs)
		return ;
	ptr = strs;
	while (*strs)
		free(*strs++);
	free(ptr);
}

static void	all_clear(char **strs, t_stack *stack)
{
	strs_clear(strs);
	stack_clear(&stack);
}

/**
 * Whatever the stack, parses a number and adds it to it
 * @param   stack    Head to add the new number to
 * @param   str     String to parse
 * @return          New stack stack
 */
t_stack	*parse_and_add_anyway(t_stack *stack, char *str)
{
	ssize_t	nbr;
	size_t	i;
	char	**strs;

	i = 0;
	strs = ft_split(str, ' ');
	while (strs[i])
	{
		nbr = ft_atol(*strs);
		if (nbr > INT_MAX || nbr < INT_MIN)
			return (all_clear(strs, stack), NULL);
		if (stack)
			stack_add_back(stack, nbr);
		else
			stack = stack_new(nbr);
		i++;
	}
	strs_clear(strs);
	return (stack);
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

	stack = NULL;
	while (argc--)
	{
		stack = parse_and_add_anyway(stack, *argv++);
		if (!stack)
			return (NULL);
	}
	return (stack);
}
