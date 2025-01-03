/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <airone01@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:18:20 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/02 17:20:35 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

int	main(int argc, char **argv)
{
	void	*result;
	char	*str;

	if (argc != 2)
		return (1);
    str = strdup("Hello");
	result = ft_memchr(str, argv[1][0], strlen(str));
	if (result)
		printf("Found at position: %ld\n", (char *)result - str);
	else
		printf("Not found\n");
	return (0);
}
