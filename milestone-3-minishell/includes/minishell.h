/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elagouch <elagouch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:15:54 by maximart          #+#    #+#             */
/*   Updated: 2025/05/08 16:46:51 by elagouch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "ft_printf.h"         // our standard functions :-)
# include "libft.h"             // our printf implementation :-)
# include <errno.h>             // errno
# include <fcntl.h>             // file control flags
# include <readline/history.h>  // rl_ utils
# include <readline/readline.h> // readline
# include <signal.h>            // signal-related functions
# include <stdbool.h>           // for booleans
# include <stdio.h>             // standard i/o
# include <stdlib.h>            // standard lib
# include <string.h>            // string operations
# include <sys/stat.h>          // stat function for files/directories
# include <sys/types.h>         // various types
# include <sys/wait.h>          // more signal-related functions

// *************************************************************************** #
//                                   Macros                                    #
// *************************************************************************** #

# define RESET "\033[039m"
# define RED "\033[091m"
# define BLUE "\033[034m"
# define GREEN "\033[092m"
# define YELLOW "\033[093m"
# define CYAN "\033[36m"

// *************************************************************************** #
//                                 Structures                                  #
// *************************************************************************** #

/**
 * @brief All types of token
 */
typedef enum e_token_type
{
	TOK_NONE,
	TOK_WORD,
	TOK_REDIR_FROM,
	TOK_REDIR_TO,
	TOK_HERE_DOC_FROM,
	TOK_HERE_DOC_TO,
	TOK_PIPE,
	TOK_OR,
	TOK_AND,
	TOK_ESP,
	TOK_NEW_LINE,
	TOK_EOF,
}						t_token_type;

typedef struct s_quote_state
{
	bool				in_single_quote;
	bool				in_double_quote;
}						t_quote_state;

/**
 * @brief Represents a command redirection
 */
typedef struct s_redir
{
	t_token_type		type;
	struct s_redir		*next;
	int					fd;
	char				*filename;
}						t_redir;

/**
 * @brief Represents a parsed token
 */
typedef struct s_token
{
	t_token_type		type;
	t_quote_state		quote;
	struct s_token		*next;
	char				*value;
}						t_token;

/**
 * @brief Represents a single command with its arguments and redirections
 */
typedef struct s_command
{
	t_token_type		operator;
	t_redir				*redirection;
	struct s_command	*next;
	char				**args;
	int					arg_count;
}						t_command;

typedef struct s_env
{
	struct s_env		*next;
	char				*key;
	char				*value;
}						t_env;

typedef struct s_fds
{
	int					in;
	int					out;
}						t_fds;

/**
 * @brief Represents the global context of the app
 */
typedef struct s_ctx
{
	t_quote_state		quote;
	t_env				*env_list;
	int					argc;
	char				**argv;
	char				**envp;
	t_token				*tokens;
	t_command			*cmd;
	int					exit_status;
	bool				exit_requested;
	int					fd_file_in;
	int					fd_file_out;
}						t_ctx;

/**
 * @brief Helper struct to track position data during processing.
 * @note Used in env management
 */
typedef struct s_pos
{
	int					start;
	int					current;
}						t_pos;

#endif
