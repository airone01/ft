/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_content_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 12:05:20 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/23 18:38:38 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

bool	is_empty_line(char *line)
{
	return (!line || line[0] == '\n' || line[0] == '\0');
}

char	*strip_newline(char *str)
{
	int	len;

	if (!str)
		return (NULL);
	len = (int)ft_strlen(str);
	if (len > 0 && str[len - 1] == '\n')
		str[len - 1] = '\0';
	return (str);
}

char	**init_requests(size_t size)
{
	char	**requests;
	size_t	i;

	requests = malloc(sizeof(char *) * (size + 1));
	if (!requests)
		return (NULL);
	i = 0;
	while (i <= size)
	{
		requests[i] = NULL;
		i++;
	}
	return (requests);
}

int	count_requests(char **content, int start)
{
	int	count;

	count = 0;
	if (!content || !content[start])
		return (0);
	while (content[start])
	{
		count++;
		start++;
	}
	return (count);
}

int	handle_pairs(void *tbl, char **content, int *i)
{
	char	*key;
	char	*value;

	while (content[*i] && content[*i + 1] && !is_empty_line(content[*i]))
	{
		key = strip_newline(content[*i]);
		value = strip_newline(content[*i + 1]);
		if (!append_to_table(tbl, key, value))
			return (0);
		*i += 2;
	}
	if (content[*i])
		(*i)++;
	return (1);
}
