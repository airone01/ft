/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/23 23:35:40 by anfichet          #+#    #+#             */
/*   Updated: 2025/02/23 23:39:04 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

int	handle_key_value(t_list *tbl[TBL_SIZE], char *key, char *value)
{
	if (!append_to_table(tbl, key, value))
	{
		free(key);
		free(value);
		error((char *)"Failed to append to table", ERR_MALLOC);
		return (1);
	}
	free(key);
	free(value);
	return (0);
}

void	handle_request(t_list *tbl[TBL_SIZE], char *line)
{
	t_list	*found;

	if (!is_empty_line(line))
	{
		found = tbl_find_node(tbl, line);
		if (found)
			ft_putendl_fd(found->value, STDOUT_FILENO);
		else
		{
			ft_putstr_fd(line, STDOUT_FILENO);
			ft_putendl_fd(": Not found.", STDOUT_FILENO);
		}
	}
	free(line);
}

int	process_pair(t_list *tbl[TBL_SIZE], char *key)
{
	char	*value;

	value = get_next_line(0);
	if (!value)
	{
		free(key);
		return (1);
	}
	value = strip_newline(value);
	return (handle_key_value(tbl, key, value));
}

int	process_line_main(t_list *tbl[TBL_SIZE], char *line, bool *reading_pairs)
{
	line = strip_newline(line);
	if (*reading_pairs)
	{
		if (is_empty_line(line))
		{
			*reading_pairs = false;
			free(line);
		}
		else if (process_pair(tbl, line))
		{
			free(line);
			return (1);
		}
	}
	else
		handle_request(tbl, line);
	return (0);
}

int	process_input(t_list *tbl[TBL_SIZE])
{
	char	*line;
	bool	reading_pairs;

	reading_pairs = true;
	line = get_next_line(0);
	while (line != NULL)
	{
		if (process_line_main(tbl, line, &reading_pairs))
			return (1);
		line = get_next_line(0);
	}
	free(line);
	return (0);
}
