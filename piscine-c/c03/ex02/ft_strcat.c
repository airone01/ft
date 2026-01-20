/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:29:12 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/16 17:13:31 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_strlen(char *str)
{
	if (*str == '\0')
		return (1);
	return (ft_strlen (str + sizeof(char)) + 1);
}

char	*ft_strcat(char *dest, char *src)
{
	int	dest_len;
	int	src_len;
	int	i;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	while (i < (src_len - 1))
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
// 	char	*src2 = "";
// 	char	*src3 = "Lorem ipsum dolor sit amet, consectetur...";
// 	char	dest[500] = "Hello, ";
// 	char	dest2[500] = "";
// 	char	dest3[1] = "";
// 	char	*rest;
//
// 	printf ("### B4\nsrc: %s\ndest: %s\n", src, dest);
// 	rest = ft_strcat(dest, src);
// 	printf ("### @R\nsrc: %s\ndest: %s\nrest: %s\n", src, dest, rest);
// 	printf ("### B4\nsrc: %s\ndest: %s\n", src2, dest2);
// 	rest = ft_strcat(dest2, src2);
// 	printf ("### @R\nsrc: %s\ndest: %s\nrest: %s\n", src2, dest2, rest);
// 	printf ("### B4\nsrc: %s\ndest: %s\n", src3, dest3);
// 	rest = ft_strcat(dest3, src3);
// 	printf ("### @R\nsrc: %s\ndest: %s\nrest: %s\n", src3, dest3, rest);
// }
