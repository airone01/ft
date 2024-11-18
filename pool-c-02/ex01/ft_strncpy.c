/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 10:54:25 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/18 20:33:09 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dest[i] = '\0';
		i++;
	}
	return (dest);
}

// int	main(void)
// {
// 	char	*src;
// 	char	dest[30];
// 	char	*rest;
//
// 	src = "hello world hello world hello world";
// 	printf("src : %s\n", src);
// 	rest = ft_strncpy(dest, src, 20);
// 	printf("src : %s\ndest: %s\nrest: %s\n", src, dest, rest);
// }
