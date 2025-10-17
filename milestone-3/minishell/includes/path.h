/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:52:22 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:05:51 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PATH_H
# define PATH_H

# include "error.h" // for t_path_error
# include "minishell.h"

// *************************************************************************** #
//                            Function Prototypes                              #
// *************************************************************************** #

// bin_find.c
char	*bin_find(t_ctx *ctx, char *bin);
bool	is_directory(const char *path);
bool	is_path(const char *str);

// bin_find_utils.c
char	*check_relative_path(char *bin, t_path_error *error_state);
void	display_path_error(char *bin, t_path_error error_state);

// bin_find_path.c
char	*bin_find_path(const char *dir, char *bin);

// path_error.c
int		handle_path_error(char *path, t_error_type err_type);
int		get_path_error_code(t_error_type err_type);

#endif
