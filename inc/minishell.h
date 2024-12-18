/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:53:38 by hui-lim           #+#    #+#             */
/*   Updated: 2024/12/18 18:16:30 by myuen            ###   ########.fr       */
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
# include "exec.h"
# include "expansion.h"
# include "parse.h"
# include "pipe.h"
# include "redirect.h"
# include "sig_control.h"
# include "token.h"

/************************************/
/*			Defination				*/
/************************************/
# ifndef PROMPT
#  define PROMPT "weneedtherapy% "
# endif

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
