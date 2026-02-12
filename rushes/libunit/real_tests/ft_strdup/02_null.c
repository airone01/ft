/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_null.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgaillet <dgaillet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 17:10:43 by dgaillet          #+#    #+#             */
/*   Updated: 2026/01/25 17:10:44 by dgaillet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../tests.h"
#include <stdlib.h>

int	strdup_null_test(void)
{
	char	*str;

	str = ft_strdup(NULL);
	if (str)
		free(str);
	return (1);
}
