/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <airone01@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:23:00 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/02 17:23:29 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include "libft.h"

int	main(int argc, char **argv)
{
	char	*s1;

	if (argc != 2)
		return (1);
	s1 = strdup("Hello");
	printf("%d\n", ft_memcmp(s1, argv[1], 5));
	return (0);
}
