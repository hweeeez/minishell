/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 17:25:16 by hui-lim           #+#    #+#             */
/*   Updated: 2025/01/19 17:25:20 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initcmdnode(t_cmdnode **cmdnode, t_node **newnode)
{
	(*newnode) = NULL;
	if (*cmdnode != NULL)
	{
		if ((*cmdnode)->args != NULL)
			freearray((*cmdnode)->args);
		free((*cmdnode)->cmd);
		free(*cmdnode);
	}
	(*cmdnode) = (t_cmdnode *)malloc(sizeof(t_cmdnode));
	(*cmdnode)->nowords = 0;
	(*cmdnode)->args = NULL;
}

int	parseword(t_node **newnode, t_cmdnode **cmdnode, char **envp, t_node **tree)
{
	if ((*cmdnode)->cmd != NULL)
	{
		if ((*newnode) == NULL || (*newnode)->type == 0)
		{
			makenewnode(newnode, tree, 1);
			(*cmdnode)->args = NULL;
			(*cmdnode)->nowords = 0;
		}		
		return (1);
	}
	else
		return (0);
}

void	parseredir(t_node **newnode, t_node **tree, t_token **tok)
{
	if ((*newnode) == NULL)
		makenewnode(newnode, tree, 1);
	makeredir(newnode, tok);
}
