/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rev_params.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 10:04:06 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/23 10:15:34 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putstr(char *str)
{
	if (*str == '\0')
		return ;
	write(1, str, 1);
	ft_putstr(str + sizeof(char));
}

void	rec_rev_params(int argc, char **argv)
{
	if (argc == 0)
		return ;
	if (argc > 1)
		rec_rev_params(argc - 1, argv + 1);
	ft_putstr(*argv);
	write(1, "\n", 1);
}

int	main(int argc, char **argv)
{
	rec_rev_params(argc - 1, argv + 1);
}
