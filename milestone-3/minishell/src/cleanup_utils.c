/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 17:36:45 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/02 16:22:41 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Safely frees a string and sets pointer to NULL
 *
 * Prevents double free issues by checking if pointer is NULL first.
 *
 * @param str Pointer to string pointer to free
 */
void	safe_free_str(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}
