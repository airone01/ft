/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_clear_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:00:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/16 16:15:58 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Clears the stack and errors out
 * @param    t_stack    Stack
 */
void	stack_clear_error(t_stack *stack_a)
{
	stack_clear(stack_a);
	std_error();
}
