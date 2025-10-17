/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anfichet <anfichet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 11:40:36 by elagouch          #+#    #+#             */
/*   Updated: 2025/02/22 21:52:10 by anfichet         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

t_list	*tbl_find_node(t_list *tbl[TBL_SIZE], char *key)
{
	t_list	*head;
	t_list	*found;
	int		index;

	if (!tbl || !key)
		return (NULL);
	index = hash_find_index(key);
	if (index < 0)
		return (NULL);
	head = tbl[index];
	if (!head)
		return (NULL);
	found = find_node(head, key);
	return (found);
}

/**
 * @brief    Appends a key-value pair to the table.
 *
 * @param    tbl        Table to append to.
 * @param    key        Key to append.
 * @param    value    Value to append.
 *
 * @return    true if the key-value pair was successfully appended,
 *            false otherwise.
 */
bool	append_to_table(t_list *tbl[TBL_SIZE], char *key, char *value)
{
	t_list	*new;
	int		index;
	char	*new_key;
	char	*new_value;

	index = hash_find_index(key);
	if (index == -1)
		return (false);
	new_key = ft_strdup(key);
	if (!new_key)
		return (false);
	new_value = ft_strdup(value);
	if (!new_value)
	{
		free(new_key);
		return (false);
	}
	new = ft_lstnew(new_key, new_value);
	if (!new)
		return (false);
	ft_lstadd_front(&tbl[index], new);
	return (true);
}
