/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   m_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:59:05 by maximart          #+#    #+#             */
/*   Updated: 2025/06/18 13:38:46 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mem.h"

bool	init_map_buffer(t_map_buffer *buffer)
{
	buffer->capacity = 50;
	buffer->count = 0;
	buffer->max_width = 0;
	buffer->lines = ft_calloc(buffer->capacity, sizeof(char *));
	return (buffer->lines == NULL);
}
