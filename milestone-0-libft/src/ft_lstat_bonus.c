/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 18:05:10 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/12 01:10:57 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// No doxygen because this is only used for libft bonuses.
t_list	*ft_lstat(t_list *lst, size_t index)
{
	size_t	i;

	i = 0;
	while (lst && i < index)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}
