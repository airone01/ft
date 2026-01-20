/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 08:26:15 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/12 09:47:49 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str)
{
	if (*str == '\0')
		return ;
	write (1, str, 1);
	ft_putstr (str + sizeof(char));
}

// int	main(void)
// {
// 	ft_putstr ("Far out in the uncharted backwaters...");
// }
