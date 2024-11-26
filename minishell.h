/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:53:38 by hui-lim           #+#    #+#             */
/*   Updated: 2024/11/23 18:56:51 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef PROMPT
#  define PROMPT "weneedtherapy% "
# endif

enum	e_tokens
{
	EXE, //includes command and all options
	FILE,
	SINGLE_RD_IN,
	DOUBLE_RD_IN,
	SINGLE_RD_OUT,
	HEREDOC, //double rd out
	PIPE,
	DOUBLE_QUOTE,
	SINGLE_QUOTE,
	DOLLAR_SIGN,
}

enum e_words
{
	//includes build ins, need to handle expanding dollar sign
}

# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

#endif
