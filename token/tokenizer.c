/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2025/01/18 19:55:50 by myuen            ###   ########.fr       */
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
	value = expand_tok(tok, start, len);
	if (!value)
		return (NULL);
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

static void	process_token_list(t_tokenizer *tok, t_token **head)
{
	t_token	*current;
	t_token	*new;

	current = NULL;
	while (!tok->error)
	{
		new = process_next_token(tok);
		if (!new)
		{
			free_token_list(head);
			return ;
		}
		if (new->type == TOKEN_EOF)
		{
			free(new);
			return ;
		}
		if (!(*head))
			*head = new;
		else
			current->next = new;
		current = new;
	}
	if (tok->error)
		free_token_list(head);
}

int	tokenize(const char *input, t_token **head, t_shell *shell)
{
	t_tokenizer	tok;

	init_tokenizer(&tok, input, shell);
	free_token_list(head);
	process_token_list(&tok, head);
	if (tok.error || !head)
	{
		if (tok.error)
			printf("Syntax Error - unclosed quotes\n");
		free_token_list(head);
		return (1);
	}
	return (0);
}
