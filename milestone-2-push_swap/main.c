/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 15:25:47 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/13 13:23:05 by elagouch         ###   ########.fr       */
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
			if (!ft_isdigit(*str) && !(*str == ' ' || (*str >= 7
						&& *str <= 15)) && !(*str == '+' || *str == '-'))
				return (0);
			str++;
		}
		argv++;
	}
	return (1);
}

static void verboser(size_t verbose, t_stack *stack)
{
    if (verbose)
    {
        stack_print(stack);
        write(1, "\n", 1);
    }
}

/**
 * Main entrypoint for push_stack
 * @param   argc    Arguments count
 * @param   argv    Arguments
 * @return          POSIX return code
 */
int	main(int argc, char **argv)
{
	t_stack	*stack;
    size_t  verbose;

	if (argc <= 1)
		return (1);
	argc--;
	argv++;
    verbose = 0;
    if (ft_strncmp(*argv, "--verbose", 100) == 0)
    {
        if (argc <= 1)
            return (1);
        argc--;
        argv++;
        verbose = 1;
    }
    if (!args_legit(argc, argv))
		return (std_error(), 1);
    stack = parse_stdin(argc, argv);
    verboser(verbose, stack);
    sort_radix(stack);
    verboser(verbose, stack);
    stack_clear(stack);
	return (0);
}
