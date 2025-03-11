/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2025/03/11 20:58:43 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_token(t_token **head, t_token *to_remove)
{
	t_token	*prev;

	if (!head || !*head || !to_remove)
		return ;
	if (to_remove == *head)
		*head = to_remove->next;
	else
	{
		prev = *head;
		while (prev && prev->next != to_remove)
			prev = prev->next;
		if (prev)
			prev->next = to_remove->next;
	}
	free(to_remove->value);
	free(to_remove);
}

static int	is_empty_word_token(t_token *token)
{
	return (token && token->type == TOKEN_WORD && \
			(!token->value || !*token->value));
}

static t_token	*handle_empty_word(t_token **head, t_token *current)
{
	t_token	*next;

	next = current->next;
	if (next && next->type == TOKEN_WORD)
	{
		remove_token(head, current);
		return (*head);
	}
	return (current->next);
}

void	merge_empty_word_tokens(t_token **head)
{
	t_token	*current;

	if (!head || !*head)
		return ;
	current = *head;
	while (current)
	{
		if (is_empty_word_token(current))
			current = handle_empty_word(head, current);
		else
			current = current->next;
	}
	if (is_empty_word_token(*head) && !(*head)->next)
		remove_token(head, *head);
}
