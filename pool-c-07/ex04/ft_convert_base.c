/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@42>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 11:26:38 by elagouch          #+#    #+#             */
/*   Updated: 2024/09/25 20:09:34 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_itoa_base(int nbr, char *base);
int		ft_strlen(char *str);

int	bad_base(char *base)
{
	int	i;
	int	j;

	if (base[0] == '\0' || base[1] == '\0')
		return (1);
	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '-' || base[i] == '+' || base[i] == ' ')
			return (1);
		j = 0;
		while (base[j] != '\0')
		{
			if (j == i && base[j + 1] != '\0')
				j++;
			else if (base[j] == base[i] && base[j + 1] != '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

/*
 * Checks i f a character is in a string
 *
 * Returns: true or false
 */
int	in_str(char c, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

/*
 * Gets the index of an element in a string
 *
 * The second condition should never be reached because we
 * check the bases beforehand.
 * But just in case, it returns -1 if there is an error.
 */
int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (1)
	{
		if (str[i] == c)
			return (i);
		if (str[i] == '\0')
			return (-1);
		i++;
	}
}

/*
 * Gets a number from a string using a base
 *
 * Returns: the resulting int
 */
int	ft_atoi_base(char *str, char *base)
{
	int	count;
	int	mult;
	int	base_len;

	count = 0;
	mult = 1;
	base_len = ft_strlen(base);
	while ((*str >= 8 && *str <= 13) || *str == ' ')
		str++;
	while ((*str == '+' || *str == '-') && *str)
	{
		if (*str == '-')
			mult = -mult;
		str++;
	}
	while (in_str(*str, base) && *str)
	{
		count = (count * base_len) + ft_strchr(base, *str);
		str++;
	}
	return (mult * count);
}

/*
 * Converts a number in a given base to another number in another given base
 */
char	*ft_convert_base(char *nbr, char *base_from, char *base_to)
{
	int	len_from;
	int	len_to;
	int	anbr;

	len_from = ft_strlen(base_from);
	len_to = ft_strlen(base_to);
	if (bad_base(base_from) || bad_base(base_to) || len_from <= 1
		|| len_to <= 1)
		return (0);
	anbr = ft_atoi_base(nbr, base_from);
	return (ft_itoa_base(anbr, base_to));
}

// #include <stdio.h>
// int	main(int argc, char **argv)
// {
// 	(void) argc;
// 	printf("%s", ft_convert_base(argv[1], argv[2], argv[3]));
// }
