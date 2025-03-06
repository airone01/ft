/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 10:18:30 by elagouch          #+#    #+#             */
/*   Updated: 2025/03/06 10:22:10 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * @brief Checks if a character is a hexadecimal digit
 *
 * @param c Character to check
 * @return t_bool True if character is hexadecimal digit, false otherwise
 */
t_bool	is_hex_digit(char c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A'
			&& c <= 'F'))
		return (true);
	return (false);
}

/**
 * @brief Converts a hex character to its integer value
 *
 * @param c Hexadecimal character (0-9, a-f, A-F)
 * @return int Integer value (0-15) or -1 if invalid
 */
int	hex_to_int(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (-1);
}

/**
 * @brief Validates hex string format and length
 *
 * @param str String to validate
 * @return t_bool True if valid format, false otherwise
 */
t_bool	validate_hex_format(char *str)
{
	int	i;
	int	len;

	if (!str || !str[0] || !str[1])
		return (false);
	if (str[0] != '0' || (str[1] != 'x' && str[1] != 'X'))
		return (false);
	i = 2;
	len = 0;
	while (str[i] && is_hex_digit(str[i]))
	{
		i++;
		len++;
	}
	if (str[i] && !ft_isspace(str[i]) && str[i] != '\0')
		return (false);
	if (len == 0 || len > 8)
		return (false);
	return (true);
}

/**
 * @brief Parse color value from hex string with validation
 *
 * @param ctx Application context
 * @param str Color string to parse
 * @param color Pointer to store parsed color
 * @return t_bool Success or failure
 */
t_bool	parse_color(t_app *ctx, char *str, unsigned int *color)
{
	unsigned int	result;
	int				i;
	int				digit_val;

	(void)ctx;
	if (!validate_hex_format(str))
		return (false);
	str += 2;
	result = 0;
	i = 0;
	while (str[i] && is_hex_digit(str[i]))
	{
		digit_val = hex_to_int(str[i]);
		if (digit_val == -1)
			return (false);
		result = (result << 4) | (unsigned int)digit_val;
		i++;
	}
	*color = result;
	return (true);
}
