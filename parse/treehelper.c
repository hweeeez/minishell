/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   treehelper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:24:57 by hui-lim           #+#    #+#             */
/*   Updated: 2025/01/29 17:24:59 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	freetree(t_node **tree)
{
	t_node	*current;
	t_node	*next;

	current = *tree;
	if (tree == NULL || *tree == NULL)//md: is this check supposed to go first?
		return ;
	while (current != NULL)
	{
		if (current->right != NULL)
			next = current->right;
		else
			next = NULL;
		if ((current)->left != NULL)
		{
			if (current->left->args != NULL)
				freearray(current->left->args);
			if (current->left->rootredir != NULL)
				freeredirs(current->left->rootredir);
			free(current->left);
			current->left = NULL;
		}
		free(current);
		current = next;
	}
}

void	freearray(char **args)
{
	int	i;

	i = 0;
	if (args == NULL)
		return ;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);
	args = NULL;
}

void	freeredirs(t_redir *redir)
{
	t_redir	*next;

	next = NULL;
	while (redir != NULL)
	{
		next = redir->next;
		if (redir->file != NULL)
			free(redir->file);
		free(redir);
		redir = next;
	}
}

void	ft_free_split(char ***split)
{
	int	i;

	i = 0;
	if (*split)
	{
		while ((*split)[i])
		{
			free((*split)[i]);
			(*split)[i] = NULL;
			i++;
		}
		free(*split);
		*split = NULL;
	}
}
