/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 09:17:25 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/16 11:13:53 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && s2[i] != '\0')
		i++;
	if (s1[i] == '\0' && s2[i] == '\0')
		return (0);
	else
		return (s1[i] - s2[i]);
}

// int	main(void)
// {
// 	printf("###\ncmp og: %d\n", strcmp("ABC", "ABC"));
// 	printf("cmp cu: %d\n", ft_strcmp("ABC", "ABC"));
// 	//
// 	printf("###\ncmp og: %d\n", strcmp("ABC", "AB"));
// 	printf("cmp cu: %d\n", ft_strcmp("ABC", "AB"));
// 	//
// 	printf("###\ncmp og: %d\n", strcmp("ABA", "ABZ"));
// 	printf("cmp cu: %d\n", ft_strcmp("ABA", "ABZ"));
// }
