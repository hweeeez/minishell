/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createtree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:11:13 by hui-lim           #+#    #+#             */
/*   Updated: 2025/01/14 21:11:16 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	inittree(t_node **tree, t_token *tokens, char **envp)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		parsetoken(&current, tree, envp);
		current = current->next;
	}
}

void	parsetoken(t_token **token, t_node **tree, char **envp)
{
	t_redir			*redir;
	static t_node	*newnode = NULL;

	if ((*tree)->left == NULL)
		newnode = NULL;
	if (isredir((*token)->type) == 1)
	{
		makeredir(&newnode, token);
		return ;
	}
	if ((*token)->type == TOKEN_PIPE)
		makenewnode(&newnode, tree, NODE_PIPE);
	if ((*token)->type == 0)
		parseword(&newnode, envp, tree, (*token)->value);
}
/*void	parsetoken(t_token **tok, t_node **tree, char **envp)
{
	t_redir				*redir;
	static t_node		*newnode = NULL;
	static t_cmdnode	*cmd = NULL;

	if ((*tree)->left == NULL)
		initcmdnode(&cmd, &newnode);
	if (isredir((*tok)->type) == 1)
	{
		makeredir(&newnode, tok);
		return ;
	}
	if ((*tok)->type == TOKEN_PIPE)
		makenewnode(&newnode, tree, NODE_PIPE);
	if ((*tok)->type == TOKEN_WORD)
	{
		cmd->cmd = ft_find_cmd_path((*tok)->value, &(cmd->args), envp);
		if (parseword(&newnode, &cmd, envp, tree) == 0)
			addarg(&(newnode->args), &(cmd->nowords), &newnode, (*tok)->value);
		else
		{
			addarg(&(newnode->args), &(cmd->nowords), &newnode, cmd->cmd);
			free(cmd->cmd);
		}
	}
}
*/

void	copyarray(char ***tocopy, int size, char *toadd)
{
	char	**temp;
	int		i;

	i = 0;
	temp = (char **)malloc(sizeof(char *) * (size + 2));
	if (*tocopy != NULL)
	{
		while ((*tocopy)[i] != NULL)
		{
			temp[i] = ft_strdup((*tocopy)[i]);
			free((*tocopy)[i]);
			i++;
		}
		free(*tocopy);
	}
	temp[i] = ft_strdup(toadd);
	temp[i + 1] = NULL;
	*tocopy = temp;
}

void	addnode(t_node **currentnode, t_node *newnode)
{
	t_node	*prevnode;

	prevnode = *currentnode;
	if (!(*currentnode))
		return ;
	if ((*currentnode)->type == 0)
	{
		assignnode(currentnode, &newnode);
	}
	else
	{
		(*currentnode) = (*currentnode)->prev;
		addnode(currentnode, newnode);
	}
}

void	assignnode(t_node **currentnode, t_node **newnode)
{
	if ((*currentnode)->left == NULL)
	{
		(*currentnode)->left = (*newnode);
		(*newnode)->prev = (*currentnode);
	}
	else if ((*currentnode)->right == NULL)
	{
		if ((*newnode)->type == 0)
		{
			(*currentnode)->right = (*newnode);
			(*newnode)->prev = (*currentnode);
			(*currentnode) = (*newnode);
		}
	}
}

//cat < main.c | grep "a" > b
//why is root->left->args[0] = cat but root->left->rootredir->file = "a"
//is it because i didmt free newnode and its static?
