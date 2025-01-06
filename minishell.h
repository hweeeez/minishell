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

# define PATH_LINE "PATH="
# define ERR_USAGE "Usage: ./pipex infile cmd1 cmd2 outfile"
# define ERR_PIPE "Pipe error"
# define ERR_FORK "Fork error"
# define ERR_CHILD "Child Exe Error"
# define ERR_CMD "Command Error"
# define ERR_FILE "File error"

# define FILE_PERMISSION 0644
# define PATH_LINE "PATH="

# define EXIT_NORMAL 0
# define EXIT_FAILURE 1
# define EXIT_CANNOT_EXE 126
# define EXIT_NOT_FOUND 127

# define FATAL_ERR_SIG 128

# include <sys/types.h>
#include <sys/wait.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <stdio.h>
#include <fcntl.h>
# include <limits.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <math.h>
#include <string.h>
#include "tokenizer.h"

struct s_node;

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
	struct s_node*   prev;
	t_node_type      type;
	char** args;         // Command and its args
	int             argc;
	t_redir* redirs;  // List of redirections for this command
	t_redir* rootredir;
	struct s_node* left;
	struct s_node* right;
}				t_node;

void	inittree(t_node** tree, t_token* tokens, char** envp);
void	parsetoken(t_token** token, t_node** tree, char** envp);
void	addnode(t_node** tree, t_node* new);
char* ft_find_cmd_path(char* cmd, char*** cmd_args, char** envp);
void copyarray(char ***tocopy, int size, char* toadd);
char* ft_strdup(const char* s);
char* ft_check_direct_path(char* cmd, char*** cmd_args);
void	ft_free_split(char ***split);
char** ft_split(char const* s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
t_node*	createnode();
void	cleantree(t_node** node);
void printTree(t_node* root);
void freetree(t_node** tree);
void    traverse_tree(t_node** root, char** envp);
void	get_pwd();
int	execute(t_node *node, char **envp);
int	exe_single(t_node *node, char **envp);
int	exe_commands(t_node *node, int input, int output, char **envp);
void executechild(t_node *node, int pipefd[2], int puts[2], char** envp);
void	closeputs(int input, int output);
int checkif_builtin(char* cmd);
int ft_strcmp(char* str1, char* str2);
int	get_redir(t_redir *redir);
int ft_heredoc(t_node *node, char **envp);

#endif
