/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:23:05 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/12 22:19:17 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

char	*ft_strupcase(char *str)
{
	int			i;
	const char	offset = 'a' - 'A';

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
		{
			str[i] -= offset;
		}
		i++;
	}
	return (str);
}

// int	main(void)
// {
// 	char	entry[] = "hello, world!";
// 	printf("here: %s\n", ft_strupcase(entry));
// }
