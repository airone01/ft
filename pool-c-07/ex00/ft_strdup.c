/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 08:51:01 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/24 10:26:20 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *str)
{
	if (*str == '\0')
		return (0);
	return (1 + ft_strlen(str + sizeof(char)));
}

/*
 * Duplicates a string.
 *
 * Returns:
 * - string if everything worked
 * - NULL if malloc failed
 */
char	*ft_strdup(char *src)
{
	int		i;
	char	*dest;

	dest = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (dest == 0)
		return (0);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// #include <stdio.h>
// int	main(int argc, char **argv)
// {
// 	char	*dest;
//
// 	(void) argc;
// 	dest = ft_strdup(argv[1]);
// 	printf("%s\n", dest);
// 	free(dest);
// }
