/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: prigaudi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 11:20:27 by prigaudi          #+#    #+#             */
/*   Updated: 2024/09/29 23:24:54 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "h_main.h"

int	ft_strlen_sani(char *str)
{
    int		i;
    int		length;

    length = 0;
    i = 0;
    while (str[i] != ' ')
    {
        if (str[i] != ' ')
            length++;
        i++;
    }
    return (length);
}

char    *ft_sanitize(char **tab, char   *str, int c)
{
    int     i;
    int     j;
    int     length;

    length = ft_strlen_sani(str);
    tab[c] = malloc(sizeof(char) * length + 1);
    if (tab[c] == NULL)
        return (NULL);
    i = 0;
    j = 0;
    while (str[i] != '\0')
    {
        if (str[i] != ' ')
        {
            tab[c][j] = str[i];
            j++;
        }
        i++;
    }
    tab[c][j] = '\0';
    return (tab[c]);
}

char	*save_word(char **tab, char *str, int *limit, int c)
{
	int	i;
	//char	*tamp;

	//printf("string = %s\n", str);
	tab[c] = malloc(sizeof(char) * (limit[1] - limit[0] + 2));
	if (tab[c] == NULL)
		return (NULL);
	i = 0;
	while (i < limit[1] - limit[0] + 1)
	{
		tab[c][i] = str[limit[0] + i];
		i++;
	}
	tab[c][i] = '\0';
	//printf("string = %s\n", tamp);
	//ft_sanitize(tab, tamp, c);
	//printf("new string = %s\n", tab[c]);
	//free(tamp);
	return (tab[c]);
}

char    **ft_split2(char *str, char *charset)
{
	int     nbr;
	int     i;
	int     limit[2];
	char    **result;
	int     c;
  
	c = 0;
	nbr = count_words(str, charset);
	result = malloc(sizeof(char *) * nbr + 1);
	if (result == NULL)
		return (result);
	i = 0;
	while (str[i])
	{
		if (str[i] > 32 && str[i] < 127)
		{
			limit[0] = i;
			while (str[i] > 32 && str[i] < 127)
			{
				if (check_charset(str, charset, i) == 1 || str[i + 1] == '\0')
				{
					limit[1] = i;
					save_word(result, str, limit, c);
					c++;
					i++;
					break ;
				}
				i++;
			}
		}
		i++;
	}
	result[c] = NULL;
	return (result);
}

char    **ft_split(char *str, char *charset)
{
    int     nbr;
    int     i;
    int     limit[2];
    char    **result;
    int     c;

    c = 0;
    nbr = count_words(str, charset);
    result = malloc(sizeof(char *) * nbr + 1);
    if (result == NULL)
        return (result);
    i = 0;
    while (str[i])
    {
        if (str[i] >= 32 && str[i] < 127)
        {
            limit[0] = i;
            while (str[i] >= 32 && str[i] < 127)
            {
                if (check_charset(str, charset, i) == 1 || str[i + 1] == '\0')
                {
                    limit[1] = i;
                    save_word(result, str, limit, c);
                    c++;
                    i++;
                    break ;
                }
                i++;
            }
        }
        i++;
    }
    result[c] = NULL;
    return (result);
}
