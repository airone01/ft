/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 17:05:38 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/14 18:03:16 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include <bsd/string.h>
//#include <stdio.h>

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size);

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < (size - 1) && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

// int	main(void)
// {
// 	char	*og = "Lorem ipsum dolor sit amet, consectetur adipiscing elit.";
// 	char	dest[500];
// 	char	dest2[500];
//
// 	printf ("### 1 ###\nOG (%zu): '%s'\nCU (%d): '%s'\n",
// 		strlcpy(dest, og, 200), dest, ft_strlcpy(dest2, og, 200), dest2);
// }
