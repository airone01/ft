/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:25:38 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/12 21:17:55 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_str_is_printable(char *str)
{
	int			i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] < ' ' || str[i] > '~')
			return (0);
		i++;
	}
	return (1);
}

// int	main(void)
// {
// 	printf("%d\n", ft_str_is_printable("HELLO"));
// 	printf("%d\n", ft_str_is_printable("Hello"));
// 	printf("%d\n", ft_str_is_printable("1\v"));
// 	printf("%d\n", ft_str_is_printable("\v"));
// 	printf("%d\n", ft_str_is_printable(""));
// }
