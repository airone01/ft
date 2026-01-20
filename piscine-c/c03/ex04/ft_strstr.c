/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 10:20:59 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/17 10:42:02 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>

char	*ft_strstr(char *str, char *to_find)
{
	int	i;
	int	j;

	if (*to_find == '\0')
		return (str);
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == to_find[0])
		{
			j = 0;
			while (str[i + j] == to_find[j] && to_find[j] != '\0')
				j++;
			if (to_find[j] == '\0')
				return (str + (i * sizeof(char)));
		}
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	printf("OG: %s\n", strstr("Hello, world!", "world"));
// 	printf("CU: %s\n", ft_strstr("Hello, wo wo wo world!", "world"));
// 	printf("OG: %s\n", strstr("Hello, world!", ""));
// 	printf("CU: %s\n", ft_strstr("Hello, world!", ""));
// 	// https://stackoverflow.com/a/11589479/11609642
// 	char	*res1 = strstr("Hello, world!", "42");
// 	printf("OG: %s\n", res1 == 0 ? "(null)" : res1);
// 	printf("CU: %s\n", ft_strstr("Hello, world!", "42"));
// }
