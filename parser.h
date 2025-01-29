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

typedef struct s_cmdnode
{
	char	**args;
	int		nowords;
	char	*cmd;
}				t_cmdnode;

void	makenewnode(t_node **newnode, t_node **tree, int type);
t_node	*createnode(void);
int		isredir(int type);
void	makeredir(t_node **newnode, t_token **token);
void	addarg(char ***args, int *nowords, t_node **node, char *add);
int		parseword(t_node **newnode, char **envp, t_node **tree, char *tok);
void	initcmdnode(t_cmdnode **cmdnode, t_node **newnode);
void	assignnode(t_node **currentnode, t_node **newnode);
void	parseredir(t_node **newnode, t_node **tree, t_token **tok);

#endif
