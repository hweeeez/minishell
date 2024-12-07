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

typedef enum e_node_type
{
	NODE_PIPE,
	NODE_COMMAND,
} t_node_type;

typedef struct s_redir
{
	t_token_type    type;       // TOKEN_REDIR_IN, TOKEN_REDIR_OUT, etc.
	char* file;      // Filename or delimiter for heredoc
	struct s_redir* next; // Multiple redirections possible
}				t_redir;

typedef struct s_node
{
	t_node          prev;
	t_node_type      type;
	char** args;         // Command and its args
	int             argc;
	t_redir* redirections;  // List of redirections for this command
	struct s_node* left;
	struct s_node* right;
}				t_node;


# include <sys/types.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
#include "tokenizer.h"

void	inittree(t_tree** tree, t_token* tokens);
void	parsetoken(t_token* token, t_tree** tree);
void	addnode(t_tree** tree, t_node* new);

#endif
