/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 12:59:21 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/18 12:59:22 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_atoi(char *str)
{
	int	count;
	int	mult;

	count = 0;
	mult = 1;
	while ((*str >= 8 && *str <= 13) || *str == ' ')
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			mult = -mult;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		count = (count * 10) + (*str - '0');
		str++;
	}
	return (mult * count);
}

// int	main(int argc, char **argv)
// {
// 	(void) argc;
// 	// printf("'%s'\n", argv[1]);
// 	printf("%d", ft_atoi(argv[1]));
// }
