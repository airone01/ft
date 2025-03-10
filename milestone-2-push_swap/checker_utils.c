/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 20:15:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/10 20:20:03 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

long	execute_s(char *line, t_stack **stack_a, t_stack **stack_b)
{
	if (!ft_strcmp("sa\n", line))
		return (sa(*stack_a, 0), 1);
	if (!ft_strcmp("sb\n", line))
		return (sb(*stack_b, 0), 1);
	if (!ft_strcmp("ss\n", line))
		return (ss(*stack_a, *stack_b, 0), 1);
	return (0);
}

long	execute_p(char *line, t_stack **stack_a, t_stack **stack_b)
{
	if (!ft_strcmp("pa\n", line))
		return (pa(stack_a, stack_b, 0), 1);
	if (!ft_strcmp("pb\n", line))
		return (pb(stack_a, stack_b, 0), 1);
	return (0);
}

long	execute_r(char *line, t_stack **stack_a, t_stack **stack_b)
{
	if (!ft_strcmp("ra\n", line))
		return (ra(stack_a, 0), 1);
	if (!ft_strcmp("rb\n", line))
		return (rb(stack_b, 0), 1);
	if (!ft_strcmp("rr\n", line))
		return (rr(stack_a, stack_b, 0), 1);
	return (0);
}

long	execute_rr(char *line, t_stack **stack_a, t_stack **stack_b)
{
	if (!ft_strcmp("rra\n", line))
		return (rra(stack_a, 0), 1);
	else if (!ft_strcmp("rrb\n", line))
		return (rrb(stack_b, 0), 1);
	else if (!ft_strcmp("rrr\n", line))
		return (rrr(stack_a, stack_b, 0), 1);
	return (0);
}

/**
 * User is responsible for clearing stack_a
 */
long	execute(t_stack **stack_a)
{
	t_stack	*stack_b;
	long	detected;
	long	fd;
	char	*line;

	fd = 0;
	stack_b = NULL;
	while (1)
	{
		line = get_next_line((int)fd);
		if (!line)
			return (stack_clear(stack_b), 1);
		if (!*line)
			return (free(line), stack_clear(stack_b), 0);
		detected = execute_s(line, stack_a, &stack_b);
		detected += execute_p(line, stack_a, &stack_b);
		detected += execute_r(line, stack_a, &stack_b);
		detected += execute_rr(line, stack_a, &stack_b);
		free(line);
		if (!detected)
			return (1);
	}
	return (stack_clear(stack_b), 0);
}
