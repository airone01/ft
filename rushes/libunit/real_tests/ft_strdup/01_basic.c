/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_basic.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:10:35 by dgaillet          #+#    #+#             */
/*   Updated: 2026/01/25 17:10:36 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"
#include <stdlib.h>

int	strdup_basic_test(void)
{
	char	*str;
	int		res;

	str = ft_strdup("Hello, World !");
	res = ft_strncmp(str, "Hello, World !", 14);
	free(str);
	return (res);
}
