/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 10:43:14 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/18 10:43:16 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
// #include <bsd/string.h>

unsigned int	ft_strlen(char *str)
{
	if (*str == '\0')
		return (0);
	return (ft_strlen (str + sizeof(char)) + 1);
}

unsigned int	ft_strlcat(char *dest, char *src, unsigned int size)
{
	unsigned int	dest_len;
	unsigned int	src_len;
	unsigned int	i;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	i = 0;
	if (size <= dest_len)
		return (src_len + size);
	while (i < (size - dest_len - 1) && src[i] != '\0')
	{
		dest[i + dest_len] = src[i];
		i++;
	}
	dest[i + dest_len] = '\0';
	return (ft_strlen(dest) - 1);
}

// int	main(void)
// {
// 	char dest11[500] = " ";
// 	char dest12[500] = " ";
// 	char dest21[500] = "Hello,";
// 	char dest22[500] = "Hello,";
// 	char dest31[500] = "";
// 	char dest32[500] = "";
// 	char *src1 = " ";
// 	char *src2 = " world!";
// 	char *src3 = "";
//
// 	// Our function
// 	int res11 = ft_strlcat(dest11, src1, 5);
// 	int res21 = ft_strlcat(dest21, src2, 0);
// 	int res31 = ft_strlcat(dest31, src3, 100);
// 	// Original
// 	int res12 = strlcat(dest12, src1, 5);
// 	int res22 = strlcat(dest22, src2, 0);
// 	int res32 = strlcat(dest32, src3, 100);
//
// 	// Assert differences
// 	if (strcmp(dest11, dest12) != 0)
// 		return printf("dest11-12");
// 	if (strcmp(dest21, dest22) != 0)
// 		return printf("dest21-22");
// 	if (strcmp(dest31, dest32) != 0)
// 		return printf("dest31-32");
// 	// Assert results
// 	if (res11 == res12)
// 		return printf("res11-12");
// 	if (res21 == res22)
// 		return printf("res21-22");
// 	if (res31 == res32)
// 		return printf("res31-32");
// }
