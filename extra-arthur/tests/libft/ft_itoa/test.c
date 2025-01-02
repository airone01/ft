/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <airone01@proton.me>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:21:44 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/02 17:22:27 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

int	main(int argc, char **argv)
{
	char	*result;
	int		n;

	if (argc != 2)
		return (1);
	n = atoi(argv[1]);
	result = ft_itoa(n);
	printf("%s\n", result);
	free(result);
	return (0);
}
