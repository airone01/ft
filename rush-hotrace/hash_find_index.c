/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_find_index.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:21:47 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/23 20:57:16 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

/**
 * @brief	Find the index of the key in the table.
 *
 * @param	key		Key to find.
 * @return	uint	Index of the key.
 */
int	hash_find_index(char *key)
{
	uint32_t	hash;
	size_t		len;

	if (!key)
		return (-1);
	len = ft_strlen(key);
	if (len == 0)
		return (-1);
	hash = fnv1a_hash(key, len);
	return (hash % TBL_SIZE);
}
