/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 09:36:19 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/18 09:36:21 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_strlen(char *str)
{
	if (*str == '\0')
		return (1);
	return (ft_strlen (str + sizeof(char)) + 1);
}

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	int	dest_len;
	int	src_len;
	int	i;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	while (i < (src_len - 1) && (unsigned int) i < nb)
	{
		dest[i + dest_len - 1] = src[i];
		i++;
	}
	dest[i + dest_len - 1] = '\0';
	return (dest);
}

// int	main(void)
// {
// 	char	*src = "world!";
// 	char	*src2 = "world!";
// 	char	dest[500] = "Hello, ";
// 	char	dest2[500] = "Hello, ";
// 	char	*rest;
//
// 	printf ("### B4\nsrc: %s\ndest: %s\n", src, dest);
// 	rest = ft_strncat(dest, src, 100);
// 	printf ("### @R\nsrc: %s\ndest: %s\nrest: %s\n", src, dest, rest);
// 	printf ("### B4\nsrc: %s\ndest: %s\n", src2, dest2);
// 	rest = ft_strncat(dest2, src2, 4);
// 	printf ("### @R\nsrc: %s\ndest: %s\nrest: %s\n", src2, dest2, rest);
// }
