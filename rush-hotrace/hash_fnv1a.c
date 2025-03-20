/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_fnv1a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 14:02:50 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/23 19:40:08 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

/**
 * @brief	Hash function FNV-1a.
 *
 * Very fast, but not the best for out use case.
 *
 * @param	data	Data to hash
 * @param	size	Size of the data in bytes
 *
 * @returns	Hashed data
 */
uint32_t	fnv1a_hash(const void *data, size_t size)
{
	const unsigned char	*bytes;
	uint32_t			hash;
	size_t				i;

	if (!data || size == 0)
		return (0);
	bytes = (const unsigned char *)data;
	hash = 2166136261u;
	i = 0;
	while (i < size && bytes[i])
	{
		hash ^= bytes[i];
		hash *= 16777619u;
		i++;
	}
	return (hash);
}
