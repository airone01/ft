/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:37:35 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/14 18:06:45 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
#include <errno.h>

//#include <stdio.h>
//
//void	stack_display(t_stack *stack)
//{
//	int		i;
//
//	i = 0;
//	printf("Index\tValue\n");
//    while (stack)
//	{
//		printf("%d\t%zd\n", i++, stack->val);
//		stack = stack->next;
//	}
//}

int	run_program(int argc, char **argv)
{
	t_stack	*stack_a;
	size_t	sorted;

	if (!args_legit(argc, argv))
		return (std_error(), 1);
	stack_a = parse_stdin(argc, argv);
	if (stack_legit(stack_a))
		return (EINVAL);
	if (execute(&stack_a))
		return (stack_clear_error(stack_a), 1);
	sorted = stack_sorted(stack_a);
	stack_clear(stack_a);
	if (sorted)
		return ((void)write(1, "OK\n", 3), 0);
	return ((void)write(1, "KO\n", 3), 1);
}

int	main(int argc, char **argv)
{
	if (argc <= 1)
		return (1);
	argc--;
	argv++;
	return (run_program(argc, argv));
}
