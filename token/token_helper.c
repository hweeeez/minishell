/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2025/01/30 19:07:33 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*handle_unexpected_quote(t_tokenizer *tok, char c,
	char **current_word)
{
	*current_word = ft_strjoin_free(*current_word, ft_chartostr(c));
	tok->position++;
	return (NULL);
}

static t_token	*final_token(t_tokenizer *tok, char *current_word)
{
	t_token	*token;

	token = NULL;
	if (tok->quote != '0')
	{
		tok->error = 1;
		free(current_word);
		return (NULL);
	}
	if (ft_strlen(current_word))
	{
		token = new_token(current_word, TOKEN_WORD, tok->word_split);
		tok->word_split = 0;
		return (token);
	}
	if (current_word)
		free(current_word);
	token = new_token(NULL, TOKEN_EOF, tok->word_split);
	tok->word_split = 0;
	return (token);
}

static t_token	*process_token_decision(t_tokenizer *tok, t_shell *shell,
	char c, char **current_word)
{
	t_token	*token;

	token = NULL;
	if (tok->quote == '0')
	{
		token = process_no_quote(tok, shell, c, current_word);
		if (token)
			return (token);
	}
	else if (tok->quote == '"')
	{
		token = process_double_quote(tok, shell, c, current_word);
		if (token)
			return (token);
	}
	else if (tok->quote == '\'')
	{
		token = process_single_quote(tok, c, current_word);
		if (token)
			return (token);
	}
	else
		handle_unexpected_quote(tok, c, current_word);
	return (NULL);
}

t_token	*process_token_loop(t_tokenizer *tok, t_shell *shell,
	char *current_word)
{
	char	c;
	t_token	*token;

	while (tok->input[tok->position])
	{
		c = tok->input[tok->position];
		token = process_token_decision(tok, shell, c, &current_word);
		if (token)
			return (token);
	}
	return (final_token(tok, current_word));
}
