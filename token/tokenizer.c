/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2025/01/08 18:22:22 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*handle_word_token(t_tokenizer *tok)
{
	char	*value;
	size_t	start;
	size_t	len;

	start = tok->position;
	while (tok->input[tok->position] && \
		!ms_is_whitespace(tok->input[tok->position]) && \
		!ms_is_special(tok->input[tok->position]) && \
		tok->input[tok->position] != '\'' && tok->input[tok->position] != '\"')
		tok->position++;
	len = tok->position - start;
	value = (char *)malloc(len + 1);
	if (!value)
		return (NULL);
	ft_strlcpy(value, tok->input + start, len + 1);
	return (new_token(value, TOKEN_WORD));
}

static t_token	*process_next_token(t_tokenizer *tok)
{
	skip_whitespace(tok);
	if (!tok->input[tok->position])
		return (new_token(NULL, TOKEN_EOF));
	if (tok->input[tok->position] == '\'' || \
		tok->input[tok->position] == '\"')
		return (new_token(handle_quote(tok), TOKEN_WORD));
	if (ms_is_special(tok->input[tok->position]))
		return (handle_special(tok));
	return (handle_word_token(tok));
}

static t_token	*process_token_list(t_tokenizer *tok, t_token *head)
{
	t_token	*current;
	t_token	*new;

	current = NULL;
	while (!tok->error)
	{
		new = process_next_token(tok);
		if (!new || new->type == TOKEN_EOF)
		{
			free(new);
			break ;
		}
		if (!head)
			head = new;
		else
			current->next = new;
		current = new;
	}
	return (head);
}

t_token	*tokenize(const char *input)
{
	t_tokenizer	tok;
	t_token		*head;

	head = NULL;
	init_tokenizer(&tok, input);
	head = process_token_list(&tok, head);
	if (tok.error || !head)
	{
		free_token_list(head);
		if (tok.error)
			printf("Syntax Error - unclosed quotes\n");
		return (NULL);
	}
	return (head);
}
