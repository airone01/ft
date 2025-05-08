/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:33:40 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 13:51:27 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MEMORY_H
# define MEMORY_H

# include "minishell.h"

// *************************************************************************** #
//                            Function Prototypes                              #
// *************************************************************************** #

// memory.c
char	*safe_strdup(t_ctx *ctx, const char *str, const char *module);
char	*safe_strjoin(t_ctx *ctx, const char *s1, const char *s2,
			const char *module);
void	*safe_malloc(t_ctx *ctx, size_t size, const char *module);
void	*safe_calloc(t_ctx *ctx, size_t nmemb, size_t size, const char *module);

// cleanup_utils.c
void	safe_free_str(char **str);

#endif
