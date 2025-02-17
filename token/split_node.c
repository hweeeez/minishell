/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_node.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:35:11 by myuen             #+#    #+#             */
/*   Updated: 2025/02/17 21:26:32 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_original_node(t_token *prev, t_token *current)
{
	if (prev)
		prev->next = current->next;
	free(current->value);
	free(current);
}

static t_token	*find_split_position(t_token *head, \
	int split_id, t_token **prev)
{
	t_token	*current;
	int		node_id;

	current = head;
	*prev = NULL;
	node_id = 0;
	while (node_id++ < split_id)
	{
		*prev = current;
		current = current->next;
	}
	return (current);
}

static void	update_head_and_link(t_token **head, t_token **prev, \
	t_token *new_node)
{
	if (!*prev)
		*head = new_node;
	else
		(*prev)->next = new_node;
	*prev = new_node;
}

void	split_node(t_token **head)
{
	t_token	*prev;
	t_token	*current;
	t_token	*new_node;
	int		split_id;

	if (!head || !*head)
		return ;
	split_id = find_split_index(*head);
	if (split_id < 0)
		return ;
	current = find_split_position(*head, split_id, &prev);
	new_node = create_first_token(&(current->value));
	update_head_and_link(head, &prev, new_node);
	create_and_link_tokens(&prev);
	remove_original_node(prev, current);
}

// void split_node(t_token **head)
// {
// 	t_token	*prev;
// 	t_token	*current;
// 	t_token *new_node;
// 	char	*value;
// 	char	*orginal;
// 	int		split_id;
// 	int		node_id;

// 	if (!head || !*head)
// 		return ;
// 	split_id = node_split_id(*head);
// 	if (split_id < 0)
// 		return ;
// 	current = *head;
// 	prev = NULL;
// 	node_id = 0;
// 	while (node_id++ < split_id)
// 	{
// 		prev = current;
// 		current = current->next;
// 	}
// 	orginal = current->value;
// 	value = ft_strtok(orginal, " \n\t");
// 	new_node = NULL;
// 	if (value)
// 		new_node = new_token(value, TOKEN_WORD, 0);
// 	if (!prev)
// 		*head = new_node;
// 	else
// 		prev->next = new_node;
// 	prev = new_node;
// 	while ((value = ft_strtok(NULL, " \n\t")))
// 	{
// 		new_node = new_token(value, TOKEN_WORD, 0);
// 		if (prev)
// 			prev->next = new_node;
// 		prev = new_node;	
// 	}
// 	if (prev)
// 		prev->next = current->next;
// 	free(current->value);
// 	free(current);
// }
