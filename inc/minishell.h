/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:53:38 by hui-lim           #+#    #+#             */
/*   Updated: 2025/01/16 19:29:28 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* MASTER INCLUDE */
#ifndef MINISHELL_H
# define MINISHELL_H

/************************************/
/*			System includes			*/
/************************************/
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>
# include <math.h>
/************************************/
/*			Library includes		*/
/************************************/
# include "libft.h"

/************************************/
/*			Project headers			*/
/************************************/
# include "builtins.h"
# include "error.h"
# include "env.h"
# include "expansion.h"
# include "token.h"
# include "parser.h"
# include "exec.h"
# include "sig_control.h"

/************************************/
/*			Defination				*/
/************************************/
# ifndef PROMPT
#  define PROMPT "weneedtherapy% "
# endif

# define EXIT_NORMAL 0
# define EXIT_FAILURE 1
# define EXIT_CANNOT_EXE 126
# define EXIT_NOT_FOUND 127

# define FATAL_ERR_SIG 128
# define HEREDOC_FILE "hd.txt"

extern int	g_received_sigint;

/*
typedef struct s_shell	t_shell;
typedef enum e_file_type	t_file_type;
typedef struct s_sigs	t_sigs;
typedef struct s_exe	t_exe;
typedef struct s_tokenizer	t_tokenizer;
typedef enum e_node_type	t_node_type;
typedef struct s_redir	t_redir;
typedef struct s_node	t_node;
typedef struct s_sigacts	t_sigacts;
typedef struct s_token	t_token;
typedef struct s_tokenizer	t_tokenizer;
*/
/*
enum	e_cmd_type
{
	EXE,
	FILENAME,
	SINGLE_RD_IN,
	DOUBLE_RD_IN,
	SINGLE_RD_OUT,
	HEREDOC,
	PIPE,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	DOLLAR_SIGN,
};*/

#endif
