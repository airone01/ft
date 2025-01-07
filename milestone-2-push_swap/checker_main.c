/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 18:37:35 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/07 19:01:49 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	bruh(t_stack *stack_a)
{
	stack_clear(stack_a);
	std_error();
}

int	main(int argc, char **argv)
{
	t_stack	*stack_a;
	size_t	sorted;

	if (argc <= 1)
		return (1);
	argc--;
	argv++;
	if (!args_legit(argc, argv))
		return (std_error(), 1);
	stack_a = parse_stdin(argc, argv);
	if (!stack_a || stack_size(stack_a) <= 1)
		return (bruh(stack_a), 1);
	stack_pos(&stack_a);
	if (stack_dupes(stack_a))
		return (bruh(stack_a), 1);
	if (execute(&stack_a))
		return (bruh(stack_a), 1);
	sorted = stack_sorted(stack_a);
	stack_clear(stack_a);
	if (sorted)
		return ((void)write(1, "OK\n", 3), 0);
	return ((void)write(1, "KO\n", 3), 1);
}
