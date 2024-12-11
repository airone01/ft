/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_del_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 10:18:20 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/11 17:43:07 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

/**
 * Deletes and frees the head of a stack
 * @param   stack   Stack to delete the head of
 */
void	stack_del_one(t_stack *stack)
{
	free(stack);
	stack = NULL;
}
