/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/11 13:06:26 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/11 13:06:27 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_strlen(const char *str)
{
	const unsigned long	*long_ptr;
	unsigned long		word;
	const char			*char_ptr = str;

	while (((unsigned long)char_ptr & (sizeof(long) - 1)) != 0)
	{
		if (!*char_ptr)
			return ((unsigned long)(char_ptr - str));
		char_ptr++;
	}
	long_ptr = (const unsigned long *)char_ptr;
	while (1)
	{
		word = *long_ptr;
		if (((word - 0x0101010101010101) & ~word & 0x8080808080808080))
			break ;
		long_ptr++;
	}
	char_ptr = (const char *)long_ptr;
	while (*char_ptr)
		char_ptr++;
	return ((unsigned long)(char_ptr - str));
}
