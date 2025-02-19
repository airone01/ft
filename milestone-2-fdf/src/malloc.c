/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:25:05 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/19 12:27:25 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	*safe_calloc(t_app *app, unsigned long nmemb, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		exit_error(app, ERR_MALLOC);
	return (ptr);
}

void	*safe_recalloc(t_app *app, void *ptr, unsigned long old_size,
		unsigned long new_size)
{
	void	*new_ptr;

	new_ptr = ft_recalloc(ptr, old_size, new_size);
	if (!new_ptr)
		exit_error(app, ERR_MALLOC);
	return (new_ptr);
}
