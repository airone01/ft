/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_clear_error.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 16:00:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/14 18:08:34 by elagouch         ###   ########.fr       */
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
