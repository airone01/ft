/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:39:18 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 15:00:13 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATION_H
# define VALIDATION_H

# include "minishell.h"

// *************************************************************************** #
//                                   Macros                                    #
// *************************************************************************** #

# define MAX_INPUT_LEN 4096
# define MAX_VAR_NAME_LEN 255

// *************************************************************************** #
//                            Function Prototypes                              #
// *************************************************************************** #

// validation.c
bool	validate_command(t_command *cmd, t_ctx *ctx);
bool	validate_env_var_name(char *name, t_ctx *ctx);
bool	validate_filename(char *filename, t_ctx *ctx);
bool	validate_input_length(char *input, t_ctx *ctx);

#endif
