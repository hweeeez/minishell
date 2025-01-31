/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createtree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:11:13 by hui-lim           #+#    #+#             */
/*   Updated: 2025/01/30 21:59:04 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	inittree(t_node **tree, t_token *tokens, char **envp)
{
	t_token	*current;

	current = tokens;
	while (current)
	{
		if (parsetoken(&current, tree, envp) == 0)
			return (0);
		current = current->next;
	}
	return (1);
}

int	parsetoken(t_token **token, t_node **tree, char **envp)
{
	static t_node	*newnode = NULL;

	if ((*tree)->left == NULL)
		newnode = NULL;
	if (isredir((*token)->type) == 1)
	{
		makeredir(&newnode, token);
		return (1);
	}
	if ((*token)->type == TOKEN_PIPE)
		makenewnode(&newnode, tree, NODE_PIPE);
	if ((*token)->type == TOKEN_WORD)
	{
		if (parseword(&newnode, envp, tree, (*token)->value) == 0)
			return (0);
	}
	return (1);
}

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
