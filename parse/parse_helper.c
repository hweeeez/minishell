/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 22:40:46 by hui-lim           #+#    #+#             */
/*   Updated: 2025/02/27 22:41:28 by hui-lim          ###   ########.fr       */
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
