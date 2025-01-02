/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:25:47 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/20 19:48:41 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "push_swap.h"

/**
 * Checks if the args passed to the app are correct
 * @param   argc    Arguments count
 * @param   argv    Arguments
 * @return          Boolean result
 */
size_t	args_legit(int argc, char **argv)
{
	char	*str;

	while (argc--)
	{
		str = *argv;
		while (*str == ' ' || (*str >= 7 && *str <= 15))
			str++;
		if (*str == '+' || *str == '-')
			str++;
		if (!*str || !ft_isdigit(*str))
			return (0);
		while (*str)
		{
			if (!ft_isdigit(*str) && !(*str == ' ' || (*str >= 7 && *str <= 15))
				&& !(*str == '+' || *str == '-'))
				return (0);
			str++;
		}
		argv++;
	}
	return (1);
}

/**
 * Chooses a sorting method depending on stack to be sorted
 * @param   stack_a Stack A
 */
void	push_swap(t_stack *stack_a)
{
	t_stack	*stack_b;
	size_t	len;

	stack_b = NULL;
	len = stack_size(stack_a);
	stack_indexes(stack_a, len);
	if (len == 2 && !stack_sorted(stack_a))
		sa(stack_a);
	else if (len == 3)
		sort_tiny(&stack_a);
	else if (len > 3 && !stack_sorted(stack_a))
		sort_large(&stack_a, &stack_b);
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
	if (!stack_a)
		return (std_error(), 1);
	push_swap(stack_a);
	stack_clear(stack_a);
	return (0);
}
