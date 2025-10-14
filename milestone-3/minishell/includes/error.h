/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:32:19 by elagouch          #+#    #+#             */
/*   Updated: 2025/05/06 14:37:34 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "minishell.h"

// *************************************************************************** #
//                                 Structures                                  #
// *************************************************************************** #

typedef enum e_error_type
{
	ERR_CMD_NOT_FOUND,
	// Fs
	ERR_NO_PERMS,
	ERR_NO_FILE,
	ERR_IS_DIR,
	ERR_NO_PWD,
	// Env
	ERR_NO_OLDPWD,
	ERR_NO_HOME,
	// Validation - input
	ERR_VLD_INPUT_LENGTH,
	// Validation - environment
	ERR_VLD_ENV_VAR_EMPTY,
	ERR_VLD_ENV_VAR_START,
	ERR_VLD_ENV_VAR_BAD_CHAR,
	ERR_VLD_ENV_VAR_TOO_LONG,
	// Validation - redirection
	ERR_VLD_REDIR_FILENAME_EMPTY,
	ERR_VLD_REDIR_FILENAME_TOO_LONG,
	// Lexer
	ERR_UNCLOSED_QUOTE,
	ERR_TOKEN_LIST,
	// Other
	ERR_IO,
	ERR_FD,
	ERR_ALLOC,
	ERR_CHILD,
	ERR_PIPE,
	ERR_IDENTIFIER,
	ERR_NUMERIC,
	ERR_TOO_MANY_ARGS,
}				t_error_type;

typedef struct s_error_info
{
	int			code;
	const char	*message;
}				t_error_info;

/**
 * @brief Simple enum proper error handling in bin_find.c
 */
typedef enum e_path_error
{
	PATH_ERR_NONE,
	PATH_ERR_NOT_FOUND,
	PATH_ERR_NO_PERMISSION,
	PATH_ERR_IS_DIR,
	PATH_ERR_OTHER
}				t_path_error;

// *************************************************************************** #
//                            Function Prototypes                              #
// *************************************************************************** #

// ctx_error_exit.c
void			ctx_error_exit(t_ctx *ctx, const char *proof,
					const char *module, t_error_type err);

// error.c
int				error_code(t_error_type err);

// error_utils.c
t_error_info	*get_error_table(void);
int				error(const char *proof, const char *module, t_error_type err);

// error_utils2.c
void			error_print(const char *proof, const char *module,
					const char *msg);

// ctx_exit.c
void			ctx_exit(t_ctx *ctx);

#endif
