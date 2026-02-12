/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_int_min.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:13:07 by dgaillet          #+#    #+#             */
/*   Updated: 2026/01/25 17:13:09 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	itoa_int_min_test(void)
{
	char	*str;
	int		res;

	str = ft_itoa(-2147483648);
	res = ft_strncmp(str, "-2147483648", 15);
	free(str);
	return (res);
}
