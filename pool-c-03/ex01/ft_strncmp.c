/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:09:52 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/16 15:20:31 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || !s1[i] || !s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	printf("###\ncmp og: %d\n", strncmp("ABC", "ABC", 100));
// 	printf("cmp cu: %d\n", ft_strncmp("ABC", "ABC", 100));
// 	//
// 	printf("###\ncmp og: %d\n", strncmp("ABC", "ABC", 2));
// 	printf("cmp cu: %d\n", ft_strncmp("ABC", "ABC", 2));
// 	//
// 	printf("###\ncmp og: %d\n", strncmp("ABC", "AB", 100));
// 	printf("cmp cu: %d\n", ft_strncmp("ABC", "AB", 100));
// 	//
// 	printf("###\ncmp og: %d\n", strncmp("ABA", "ABZ", 100));
// 	printf("cmp cu: %d\n", ft_strncmp("ABA", "ABZ", 100));
// 	//
// 	printf("###\ncmp og: %d\n", strncmp("ABCEEFGH", "ABCDEFGH", 5));
// 	printf("cmp cu: %d\n", ft_strncmp("ABCEEFGH", "ABCDEFGH", 5));
// 	//
// 	printf("###\ncmp og: %d\n", strncmp("ABCDEFGHIJK", "ONMLKJIHGFE", 8));
// 	printf("cmp cu: %d\n", ft_strncmp("ABCDEFGHIJK", "ONMLKJIHGFE", 8));
// }
