/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 16:12:57 by elagouch          #+#    #+#             */
/*   Updated: 2025/01/29 16:58:21 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
 * @brief	Frees the strings in a list as pointers
 */
static void	free_ptrs(void *str)
{
	free_strings((char **)str);
}

/**
 * @brief	Frees the whole app structure
 */
void	app_free(t_app app)
{
	if (app.fds[0] != -1)
		close(app.fds[0]);
	if (app.fds[1] != -1)
		close(app.fds[1]);
	free(app.file1);
	free(app.file2);
	if (app.cmds)
		ft_lstclear(&app.cmds, free_ptrs);
	free(app.cmds);
}
