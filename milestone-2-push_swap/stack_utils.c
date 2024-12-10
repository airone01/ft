/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:09:11 by elagouch          #+#    #+#             */
/*   Updated: 2024/12/10 18:20:20 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Frees a stack
 * @param   stack   stack
 */
void free_stack(char **stack)
{
    while (*stack)
        free(*stack++);
    free(stack);
    stack = NULL;
}
