/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_negatif.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:12:34 by dgaillet          #+#    #+#             */
/*   Updated: 2026/01/25 17:12:34 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"

int	itoa_negatif_test(void)
{
	char	*str;
	int		res;

	str = ft_itoa(-42);
	res = ft_strncmp(str, "-42", 10);
	free(str);
	return (res);
}
