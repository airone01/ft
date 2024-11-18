/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rush_check_charset.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 16:14:17 by prigaudi          #+#    #+#             */
/*   Updated: 2024/09/29 23:25:47 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
 * Validates the charset.
 */
int	check_charset(char *str, char *charset, int i)
{
	int	j;

	j = 0;
    while (charset[j])
    {
        if (charset[j] != str[i + 1])
            return (0);
        i++;
        j++;
    }
    return (1);
}
