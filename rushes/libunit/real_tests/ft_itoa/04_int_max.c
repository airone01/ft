/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_int_max.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:12:57 by dgaillet          #+#    #+#             */
/*   Updated: 2026/01/25 17:12:58 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	itoa_int_max_test(void)
{
	char	*str;
	int		res;

	str = ft_itoa(2147483647);
	res = ft_strncmp(str, "2147483647", 15);
	free(str);
	return (res);
}
