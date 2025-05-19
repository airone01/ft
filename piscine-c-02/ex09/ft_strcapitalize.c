/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcapitalize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <erwann.lagouche@gmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 11:33:00 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/18 08:40:54 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	is_alphanum(char str)
{
	if ((str >= '0' && str <= '9')
		|| (str >= 'A' && str <= 'Z')
		|| (str >= 'a' && str <= 'z'))
		return (1);
	return (0);
}

int	ucase(char str)
{
	const char	offset = 'a' - 'A';

	if (str >= 'a' && str <= 'z')
		return (str - offset);
	return (str);
}

int	lcase(char str)
{
	const char	offset = 'a' - 'A';

	if (str >= 'A' && str <= 'Z')
		return (str + offset);
	return (str);
}

char	*ft_strcapitalize(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		str[i] = lcase(str[i]);
		i++;
	}
	i = 0;
	if (is_alphanum(str[0]))
		str[i] = ucase(str[i]);
	while (str[i] != '\0')
	{
		if (is_alphanum(str[i]) && !is_alphanum(str[i - 1]))
			str[i] = ucase(str[i]);
		i++;
	}
	return (str);
}

// int	main(void)
// {
// 	char	entry[] = "salut, comment tu vas ?
// 		42mots quarante-deux; cinquante+et+un";
// 	char	*res;
//
// 	printf("entry: \"%s\"\n", entry);
// 	res = ft_strcapitalize (entry);
// 	printf("entry: \"%s\"\nres  : \"%s\"\n", entry, res);
// }
