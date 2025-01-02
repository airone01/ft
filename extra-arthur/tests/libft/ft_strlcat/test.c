/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <airone01@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:26:40 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/02 17:27:32 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

// Test with limited buffer
int	main(int argc, char **argv)
{
	size_t	result;
	size_t	size;
	char	dest[50];

	if (argc != 2)
		return (1);
	size = 10;
	memset(dest, 'x', sizeof(dest));
	dest[0] = 'h';
	dest[1] = 'i';
	dest[2] = '\0';
	result = ft_strlcat(dest, argv[1], size);
	printf("Result: %zu\nBuffer: %s\n", result, dest);
	return (0);
}
