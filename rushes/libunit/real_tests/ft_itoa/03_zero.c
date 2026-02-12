/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_zero.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:12:43 by dgaillet          #+#    #+#             */
/*   Updated: 2026/01/25 17:12:44 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	itoa_zero_test(void)
{
	char	*str;
	int		res;

	str = ft_itoa(0);
	res = ft_strncmp(str, "0", 10);
	free(str);
	return (res);
}
