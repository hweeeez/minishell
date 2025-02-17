/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_node_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:35:11 by myuen             #+#    #+#             */
/*   Updated: 2025/02/17 21:29:08 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	node_split_id(t_token *head)
{
	t_token	*current;
	int		i;

	i = -1;
	current = head;
	while (current)
	{
		i++;
		if (current->need_to_split == 1)
			return (i);
		else
		{
			current = current->next;
		}	
	}
	return (-1);
}

int	find_split_index(t_token *head)
{
	if (!head)
		return (-1);
	return (node_split_id(head));
}

t_token	*create_first_token(char **orginal)
{
	char	*value;
	t_token	*new_node;

	value = ft_strtok(*orginal, " \n\t");
	if (!value)
		return (NULL);
	new_node = new_token(value, TOKEN_WORD, 0);
	return (new_node);
}

void	create_and_link_tokens(t_token **prev)
{
	char	*value;
	t_token	*new_node;

	value = ft_strtok(NULL, " \n\t");
	while (value)
	{
		new_node = new_token(value, TOKEN_WORD, 0);
		if (*prev)
			(*prev)->next = new_node;
		*prev = new_node;
		value = ft_strtok(NULL, " \n\t");
	}
}
