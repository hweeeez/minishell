/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   llist_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2025/01/18 18:02:29 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*new_token(char *value, t_token_type type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	free_token_list(t_token **head)
{
	t_token	*temp;

	if (!head || !*head)
		return ;
	while (*head)
	{
		temp = (*head)->next;
		if ((*head)->value)
			free((*head)->value);
		free(*head);
		*head = temp;
	}
}

t_token	*ft_tokenlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst -> next != NULL)
		lst = lst -> next;
	return (lst);
}

void add_token(t_token *head, t_token *new)
{
	t_token	*current;

	current = ft_tokenlast(head);
	if (current)
	{
		current->next = new;
		printf("adding current->next %s\n", new->value);
	}
	else
	{
		printf("adding new->next %s\n", new->value);
		head = new;
	}
}
