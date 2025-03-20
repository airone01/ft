/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_content.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:22:37 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/23 22:31:19 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static bool	do_stuff(char **requests, char *str, int *j)
{
	if (str[0] != '\0')
	{
		requests[*j] = ft_strdup(str);
		if (!requests[*j])
			return (false);
		(*j)++;
	}
	return (true);
}

static bool	handle_requests(char **content, char **requests, int start)
{
	int		i;
	int		j;
	char	*str;

	i = start;
	j = 0;
	if (!content || !requests)
		return (false);
	while (content[i])
	{
		if (is_empty_line(content[i]))
		{
			i++;
			continue ;
		}
		str = strip_newline(content[i]);
		if (!str)
			return (false);
		if (!do_stuff(requests, str, &j))
			return (false);
		i++;
	}
	requests[j] = NULL;
	return (true);
}

static char	**parse_requests(int *req_count, char **content, int i)
{
	char	**requests;

	*req_count = count_requests(content, i);
	if (*req_count <= 0)
		return (init_requests(0));
	requests = init_requests(*req_count);
	if (!requests)
		return (NULL);
	if (!handle_requests(content, requests, i))
	{
		free_2d_array((void **)requests);
		return (NULL);
	}
	return (requests);
}

/**
 * @brief	Parses the content.
 *
 * @param	content	The content of the file.
 *
 * @returns	char**	The requests.
 */
char	**parse_content(void *tbl, char **content)
{
	int	i;
	int	req_count;

	if (!content || !tbl)
		return (NULL);
	i = 0;
	while (content[i] && is_empty_line(content[i]))
		i++;
	if (!handle_pairs(tbl, content, &i))
		return (NULL);
	while (content[i] && is_empty_line(content[i]))
		i++;
	if (!content[i])
		return (init_requests(0));
	return (parse_requests(&req_count, content, i));
}
