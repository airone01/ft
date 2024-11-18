/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 20:25:38 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/12 20:26:03 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_str_is_alpha(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((str[i] < 'A' || str[i] > 'Z') && (str[i] < 'a' || str[i] > 'z'))
			return (0);
		i++;
	}
	return (1);
}

// int	main(void)
// {
// 	printf("%d\n", ft_str_is_alpha("hello"));
// 	printf("%d\n", ft_str_is_alpha("hello world"));
// 	printf("%d\n", ft_str_is_alpha(" "));
// 	printf("%d\n", ft_str_is_alpha("]"));
// 	printf("%d\n", ft_str_is_alpha("a"));
// 	printf("%d\n", ft_str_is_alpha(""));
// }
