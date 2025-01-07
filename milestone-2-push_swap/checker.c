/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:15:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/07 19:12:23 by elagouch         ###   ########.fr       */
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
	size_t	fd;

	fd = 0;
	stack_b = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line || !*line)
			return (free(line), 0);
		res = 0;
		res += execute_s(line, stack_a, &stack_b);
		res += execute_p(line, stack_a, &stack_b);
		res += execute_r(line, stack_a, &stack_b);
		res += execute_rr(line, stack_a, &stack_b);
		free(line);
		if (res == 0)
			return (1);
	}
	return (0);
}
