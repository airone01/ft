/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 21:23:05 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/13 11:30:12 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

char	*ft_strlowcase(char *str)
{
	int			i;
	const char	offset = 'a' - 'A';

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
		{
			str[i] += offset;
		}
		i++;
	}
	return (str);
}

// int	main(void)
// {
// 	char	entry[] = "HELLO, WORLD!";
// 	printf("here: %s\n", ft_strlowcase(entry));
// }
