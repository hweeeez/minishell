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

typedef struct s_tree
{
	s_pipe*		root;
}				t_tree;

typedef struct s_pipe
{
	t_pipe		pipe;
	t_command*	commands;
}				t_pipe;

typedef struct s_command
{
	char**		args;
	t_redir*	redirs;
}				t_pipe;

typedef struct s_redir
{
	char*	file;
	int		type;
}				t_redir;

# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>

#endif
