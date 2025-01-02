/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <airone01@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:24:01 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/02 17:24:30 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	main(int argc, char **argv)
{
	size_t	len;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <string>\n", argv[0]);
		return (1);
	}
	len = ft_strlen(argv[1]);
	printf("%zu\n", len);
	return (0);
}
