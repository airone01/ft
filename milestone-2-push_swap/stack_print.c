/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_printf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 17:01:34 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/11 17:43:31 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	stack_print_one(t_stack *stack)
{
	ft_printf("%d,", stack->val);
}

/**
 * Displays a stack to the standard output
 * @param   stack   Stack to printf
 */
void	stack_print(t_stack *stack)
{
	stack_iter(stack, stack_print_one);
}
