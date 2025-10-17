/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 22:13:58 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/02 22:32:30 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	g_no_match = 0;
int	g_invalid_base = 0;

int	symbol_set(char c, char *symbols)
{
	while ((c != *symbols) && *symbols)
		symbols++;
	if (!*symbols)
		return (0);
	return (1);
}

int	ft_isspace(char *str)
{
	if ((*str >= 9 && *str <= 13) || *str == 32)
		return (1);
	else
		return (0);
}

int	ft_pow(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	return (ft_pow(nb, power - 1) * nb);
}

int	twice_char(char *symbols)
{
	int	i;
	int	j;

	i = 0;
	while (*(symbols + i))
	{
		j = i + 1;
		while (*(symbols + j))
		{
			if (*(symbols + i) == *(symbols + j))
				return (1);
			++j;
		}
		++i;
	}
	return (0);
}

int	real_value(char *nbr, char *symbols, int baseValue, int position, int sign)
{
	int	i;

	i = 0;
	if (!position)
	{
		while (*nbr != *(symbols + i))
			++i;
		return (i * sign);
	}
	else
	{
		while (*nbr != *(symbols + i))
			++i;
		return (real_value(nbr + 1, symbols, baseValue, position - 1, sign) + (i
				* ft_pow(baseValue, position) * sign));
	}
}

int	ft_atoi_base(char *str, char *base)
{
	int	baseValue;
	int	position;
	int	sign;

	sign = +1;
	baseValue = 0;
	position = 0;
	while (base[baseValue])
	{
		if (base[baseValue] == '+' || base[baseValue] == '-'
			|| base[baseValue] == ' ')
		{
			g_invalid_base = 1;
			return (0);
		}
		++baseValue;
	}
	if (baseValue < 2)
	{
		g_invalid_base = 1;
		return (0);
	}
	if (twice_char(base))
	{
		g_invalid_base = 1;
		return (0);
	}
	while (*(str + position))
	{
		while (*str == '+' || *str == '-' || ft_isspace(str))
		{
			if (*str == '-')
				sign *= -1;
			++str;
		}
		if (!symbol_set(*(str + position), base))
		{
			g_no_match = 1;
			return (0);
		}
		++position;
	}
	return (real_value(str, base, baseValue, position - 1, sign));
}
