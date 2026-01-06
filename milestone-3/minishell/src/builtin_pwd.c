/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_pwd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:54:32 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 14:00:06 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"

/**
 * @brief Executes the pwd built-in command
 *
 * @return int Exit status (0 for success, non-zero for error)
 */
int	builtin_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (error(NULL, "pwd", ERR_NO_PWD));
	ft_printf("%s\n", pwd);
	free(pwd);
	return (0);
}
