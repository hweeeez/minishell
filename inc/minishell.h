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
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>
/************************************/
/*			Library includes		*/
/************************************/
# include "libft.h"

/************************************/
/*			Project headers			*/
/************************************/
# include "builtins.h"
# include "heredoc.h"
# include "error.h"
# include "env.h"
# include "expansion.h"
# include "token.h"
# include "parser.h"
# include "exec.h"
# include "pipe.h"
# include "redirect.h"
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

/*These should be moved elsewhere?*/
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
};

#endif
