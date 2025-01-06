/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:15:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/06 20:38:14 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

size_t	execute_s(char *line, t_stack **stack_a, t_stack **stack_b)
{
	if (ft_strncmp("sa", line, INT_MAX))
		sa(*stack_a);
	else if (ft_strncmp("sb", line, INT_MAX))
		sb(*stack_b);
	else if (ft_strncmp("ss", line, INT_MAX))
		ss(*stack_a, *stack_b);
	else
		return (0);
	return (1);
}

size_t	execute_p(char *line, t_stack **stack_a, t_stack **stack_b)
{
	if (ft_strncmp("pa", line, INT_MAX))
		pa(stack_a, stack_b);
	else if (ft_strncmp("pb", line, INT_MAX))
		pb(stack_a, stack_b);
	else
		return (0);
	return (1);
}

size_t	execute_r(char *line, t_stack **stack_a, t_stack **stack_b)
{
	if (ft_strncmp("ra", line, INT_MAX))
		ra(stack_a);
	else if (ft_strncmp("rb", line, INT_MAX))
		rb(stack_b);
	else if (ft_strncmp("rr", line, INT_MAX))
		rr(stack_a, stack_b);
	else
		return (0);
	return (1);
}

size_t	execute_rr(char *line, t_stack **stack_a, t_stack **stack_b)
{
	if (ft_strncmp("rra", line, INT_MAX))
		ra(stack_a);
	else if (ft_strncmp("rrb", line, INT_MAX))
		rb(stack_b);
	else if (ft_strncmp("rrr", line, INT_MAX))
		rr(stack_a, stack_b);
	else
		return (0);
	return (1);
}

size_t	execute(t_stack **stack_a)
{
	t_stack	*stack_b;
	char	*line;
	size_t	res;

	stack_b = NULL;
	line = get_next_line(0);
	while (line)
	{
		line = get_next_line(0);
		res = 0;
		res += execute_s(line, stack_a, &stack_b);
		res += execute_p(line, stack_a, &stack_b);
		res += execute_r(line, stack_a, &stack_b);
		res += execute_rr(line, stack_a, &stack_b);
		if (res == 0)
			return (1);
	}
	return (0);
}

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
	execute(&stack_a);
	if (stack_sorted(stack_a))
		return ((void)write(1, "OK\n", 3), 0);
	return ((void)write(1, "KO\n", 3), 1);
}
