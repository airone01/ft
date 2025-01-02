/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <airone01@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:25:37 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/02 17:26:22 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

// Test with limited buffer
int	main(int argc, char **argv)
{
	size_t	result;
	size_t	size;
	char	dest[50];

	if (argc != 2)
		return (1);
	size = 5;
	result = ft_strlcpy(dest, argv[1], size);
	printf("Result: %zu\nBuffer: %s\n", result, dest);
	return (0);
}
