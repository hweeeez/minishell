/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2025/01/30 20:19:30 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*process_next_token(t_tokenizer *tok, t_shell *shell)
{
	char	*current_word;

	current_word = ft_strdup("");
	skip_whitespace(tok);
	tok->quote = '0';
	return (process_token_loop(tok, shell, current_word));
}

static void	process_token_list(t_tokenizer *tok, t_token **head, t_shell *shell)
{
	t_token	*current;
	t_token	*new;

	current = NULL;
	while (!tok->error)
	{
		new = process_next_token(tok, shell);
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
	free_token_list(head); //every new line is a new tokenlist
	process_token_list(&tok, head, shell);
	if (tok.error || !head)
	{
		if (tok.error)
		{
			ft_putstr_fd("Syntax Error : unclosed quotes or"
				" other errors\n", STDERR_FILENO);
			free_token_list(head);
			return (1);
		}
	}
	//split_token function
	return (validate_token_syntax(*head));
}
// static t_token	*process_next_token(t_tokenizer *tok)
// {
// 	skip_whitespace(tok);
// 	if (!tok->input[tok->position])
// 		return (new_token(NULL, TOKEN_EOF));
// 	if (tok->input[tok->position] == '\'' || 
// 		tok->input[tok->position] == '\"')
// 		return (new_token(handle_quote(tok), TOKEN_WORD));
// 	if (ms_is_special(tok->input[tok->position]))
// 		return (handle_special_token(tok));
// 	return (handle_word_token(tok));
// }
