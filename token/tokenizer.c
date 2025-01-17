/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2025/01/17 21:29:53 by myuen            ###   ########.fr       */
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
	new = process_next_token(tok);
	while (!tok->error && new)
	{
		if (!new || new->type == TOKEN_EOF)
		{
			free(new);
			break ;
		}
		if ((*head) == NULL)
		{
			*head = new;
			current = *head;
		}
		else
		{
			current = ft_tokenlast(*head);
			current->next = new;
		}
		current = new;
		new = process_next_token(tok);
	}
}

int	tokenize(const char *input, t_token **head, t_shell *shell)
{
	t_tokenizer	tok;

	init_tokenizer(&tok, input, shell);
	process_token_list(&tok, head);
	if (tok.error || !head)
	{
		if (tok.error)
			printf("Syntax Error - unclosed quotes\n");
		return (1);
	}
	return (0);
}
// static void    process_token_list(t_tokenizer *tok, t_token **head)
// {
//     t_token    *current;
//     t_token    *new;
//     int        token_count;

//     token_count = 0;
//     printf("\n=== Starting Tokenization ===\n");
//     new = process_next_token(tok);
//     printf("First token processed: %p\n", (void *)new);

//     while (!tok->error && new)
//     {
//         printf("\n--- Token #%d ---\n", token_count + 1);
//         if (!new || new->type == TOKEN_EOF)
//         {
//             printf("EOF or NULL token encountered\n");
//             free(new);
//             break;
//         }

//         printf("Token content: '%s'\n", new->value ? new->value : "NULL");
//         printf("Token type: %d\n", new->type);

//         if ((*head) == NULL)
//         {
//             printf("Setting head token\n");
//             *head = new;
//             current = *head;
//             printf("Head token set: %p\n", (void *)*head);
//             printf("Current points to: %p\n", (void *)current);
//         }
//         else
//         {
// 			current = *head;
// 			while (current->next)
// 				current = current->next;
//             printf("Adding to list\n");
//             printf("Current token: %p\n", (void *)current);
//             printf("New token: %p\n", (void *)new);
//             current->next = new;
//             printf("Link created: %p -> %p\n", (void *)current, (void *)current->next);
//         }

//         current = new;
//         printf("Moving current to: %p\n", (void *)current);
//         token_count++;

//         new = process_next_token(tok);
//         printf("Next token processed: %p\n", (void *)new);
//     }

//     printf("\n=== Tokenization Complete ===\n");
//     printf("Total tokens processed: %d\n", token_count);
//     printf("Final head points to: %p\n", (void *)*head);
//     if (*head)
//         printf("First token content: '%s'\n", (*head)->value ? (*head)->value : "NULL");
// }
