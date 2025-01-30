/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:11:40 by hui-lim           #+#    #+#             */
/*   Updated: 2025/01/14 21:11:42 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	makenewnode(t_node **newnode, t_node **tree, int type)
{
	(*newnode) = createnode();
	(*newnode)->type = type;
	addnode(tree, *newnode);
}

void	addarg(char ***args, int *nowords, char *add)
{
	copyarray(args, *nowords, add);
	(*nowords)++;
}

t_node	*createnode(void)
{
	t_node	*node;

	node = (t_node *)malloc(sizeof(t_node));
	node->left = NULL;
	node->right = NULL;
	node->type = NODE_PIPE;
	node->prev = NULL;
	node->rootredir = NULL;
	node->redirs = NULL;
	node->args = NULL;
	node->argc = 0;
	return (node);
}

void	parseword(t_node **newnode, char **envp, t_node **tree, char *tok)
{
	char		*word;
	static int	nowords;

	word = ft_find_cmd_path(tok, &((*newnode)->args), envp);
	if (word != NULL)
	{
		if ((*newnode) == NULL || (*newnode)->type == 0)
		{
			makenewnode(newnode, tree, NODE_COMMAND);
			nowords = 0;
		}
		else if ((*newnode)->args != NULL)
			word = tok;
		copyarray(&(*newnode)->args, nowords, word);
		free(word);
	}
	else
		copyarray(&(*newnode)->args, nowords, tok);
	nowords++;
}

void	parseredir(t_node **newnode, t_node **tree, t_token **tok)
{
	if ((*newnode) == NULL)
		makenewnode(newnode, tree, 1);
	makeredir(newnode, tok);
}
