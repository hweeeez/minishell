/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 17:43:35 by hui-lim           #+#    #+#             */
/*   Updated: 2025/01/18 17:43:52 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

# define PATH_LINE "PATH="

struct	s_node;

typedef enum e_node_type
{
	NODE_PIPE,
	NODE_COMMAND,
}				t_node_type;

typedef struct s_redir
{
	t_token_type	type;
	char			*file;
	struct s_redir	*next;
}				t_redir;

typedef struct s_node
{
	struct s_node	*prev;
	t_node_type		type;
	char			**args;
	int				argc;
	t_redir			*redirs;
	t_redir			*rootredir;
	struct s_node	*left;
	struct s_node	*right;
}				t_node;

void	makenewnode(t_node **newnode, t_node **tree, int type);
t_node	*createnode(void);
int		isredir(int type);
void	makeredir(t_node **newnode, t_token **token);
void	addarg(char ***args, int *nowords, char *add);
int		parseword(t_node **newnode, t_shell **shell, t_node **tree, char *tok);
void	assignnode(t_node **currentnode, t_node **newnode);
void	parseredir(t_node **newnode, t_node **tree, t_token **tok);
int		parsetoken(t_token **token, t_node **tree, t_shell **shell);
char	*ft_check_direct_path(char *cmd, char ***cmd_args);
char	*ft_find_cmd_path(char *cmd, char ***cmd_args, char **envp);
void	ft_free_split(char ***split);
void	addnode(t_node **currentnode, t_node *newnode);
void	copyarray(char ***tocopy, int size, char *toadd);
void	freearray(char **args);
void	freeredirs(t_redir *redir);
void	freetree(t_node **tree);
int		inittree(t_node **tree, t_token *tokens, t_shell **shell);
int		check_dir_exists(char *path);
void    print_parse_error(char *cmd, char *error, int status, t_shell **shell);

#endif
