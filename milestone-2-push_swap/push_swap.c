/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:25:47 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/06 20:52:50 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Finds the element of a stack with the lowest index.
 * This element will be the head at the end since we sort the stack.
 * Then it will be used for clearing the whole stack.
 * @param	stack	Stack to search
 * @return			Head of the stack
 */
t_stack	*stack_lowest(t_stack *stack)
{
	t_stack	*found;

	if (!stack)
		return (NULL);
	found = stack;
	while (stack->next)
	{
		if (found && stack->idx < found->idx)
			found = stack;
		stack = stack->next;
	}
	return (found);
}

/**
 * Chooses a sorting method depending on stack to be sorted.
 * @param   stack_a Stack A
 * @returns			The lowest (and first) element of the
 * 					stack to easily free the stack
 */
t_stack	*push_swap(t_stack *stack_a)
{
	t_stack	*stack_b;
	t_stack	*stack_a_start;
	size_t	len;

	stack_b = NULL;
	len = stack_size(stack_a);
	stack_indexes(stack_a, len);
	stack_a_start = stack_lowest(stack_a);
	if (len == 2 && !stack_sorted(stack_a))
		sa(stack_a);
	else if (len == 3)
		sort_tiny(&stack_a);
	else if (len > 3 && !stack_sorted(stack_a))
		sort_large(&stack_a, &stack_b);
	return (stack_a_start);
}

/**
 * Main entrypoint for push_stack
 * @param   argc    Arguments count
 * @param   argv    Arguments
 * @return          POSIX return code
 */
int	main(int argc, char **argv)
{
	t_stack	*stack_a;

	if (argc <= 1)
		return (1);
	argc--;
	argv++;
	if (!args_legit(argc, argv))
		return (std_error(), 1);
	stack_a = parse_stdin(argc, argv);
	if (!stack_a || stack_size(stack_a) <= 1 || stack_dupes(stack_a))
	{
		stack_clear(stack_a);
		std_error();
		return (1);
	}
	stack_a = push_swap(stack_a);
	stack_clear(stack_a);
	return (0);
}
