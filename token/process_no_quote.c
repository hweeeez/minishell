/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_no_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:53:25 by myuen             #+#    #+#             */
/*   Updated: 2025/01/30 20:33:26 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*handle_space(t_tokenizer *tok, char **current_word)
{
	t_token	*token;

	if (ft_strlen(*current_word))
	{
		token = new_token(*current_word, TOKEN_WORD, \
				tok->word_split, tok->hd_quote);
		tok->word_split = 0;
		tok->hd_quote = 0;
		tok->position++;
		return (token);
	}
	tok->position++;
	return (NULL);
}

static t_token	*handle_special(t_tokenizer *tok, char **current_word)
{
	t_token	*token;

	if (ft_strlen(*current_word))
	{
		token = new_token(*current_word, TOKEN_WORD, \
				tok->word_split, tok->hd_quote);
		tok->word_split = 0;
		tok->hd_quote = 0;
		return (token);
	}
	free(*current_word);
	return (handle_special_token(tok));
}

static void	handle_expansion(t_tokenizer *tok, t_shell *shell,
	char **current_word)
{
	char	*expanded;

	expanded = expand(tok, shell);
	if (expanded)
	{
		if (tok->quote == '0')
		{
			if (!ft_isnowhitespace((const char *) expanded))
			{
				tok->word_split = 1;
				if (pre_is_redir(shell->token))
					tok->ambiguous = 1;
			}
		}
		*current_word = ft_strjoin_free(*current_word, expanded);
	}
}

static t_token	*process_empty_quote(t_tokenizer *tok,
		char quote, char **current_word)
{
	t_token	*token;
	int		is_empty_quotes;
	int		current_word_empty;
	int		followed_by_delimiter;

	is_empty_quotes = (tok->input[tok->position + 1] == quote);
	current_word_empty = !ft_strlen(*current_word);
	followed_by_delimiter = is_delimiter(tok->input[tok->position + 2]);
	if (is_empty_quotes && current_word_empty && followed_by_delimiter)
	{
		if (last_token_type(tok->shell->token) == TOKEN_HEREDOC)
			tok->hd_quote = 1;
		token = new_token(*current_word, TOKEN_WORD, \
				tok->word_split, tok->hd_quote);
		tok->word_split = 0;
		tok->hd_quote = 0;
		tok->position += 2;
		return (token);
	}
	return (NULL);
}

t_token	*process_no_quote(t_tokenizer *tok, t_shell *shell, char c, \
	char **current_word)
{
	t_token	*token;

	if (ft_isspace(c))
		return (handle_space(tok, current_word));
	if (c == '\'' || c == '"')
	{
		token = process_empty_quote(tok, c, current_word);
		if (token)
			return (token);
		tok->hd_quote = 1;
		tok->quote = c;
		tok->position++;
		return (NULL);
	}
	if (ms_is_special(c))
		return (handle_special(tok, current_word));
	if (c == '$' && !pre_is_heredoc(shell->token))
	{
		handle_expansion(tok, shell, current_word);
		return (NULL);
	}
	*current_word = ft_strjoin_free(*current_word, ft_chartostr(c));
	tok->position++;
	return (NULL);
}

/*
static int	next_is_special(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

static t_token	*process_empty_quote(t_tokenizer *tok, \
	char quote, char **current_word)
{
	t_token			*token;
	t_token_type	prev_type;

	prev_type = last_token_type(tok->shell->token);
	if (tok->input[tok->position + 1] == quote && !ft_strlen(*current_word) && \
		((!tok->input[tok->position + 2] || 
		ft_isspace(tok->input[tok->position + 2]))) || 
		(prev_type == TOKEN_HEREDOC && 
		next_is_special(tok->input[tok->position + 2])))
	{
		token = new_token(*current_word, TOKEN_WORD, \
			tok->word_split, tok->hd_quote);
		tok->word_split = 0;
		tok->hd_quote = 0;
		tok->position += 2;
		return (token);
	}
	return (NULL);
}

static void	handle_quotes(t_tokenizer *tok, char quote_type)
{
	tok->quote = quote_type;
	tok->position++;
}

t_token	*handle_word_token(t_tokenizer *tok)
{
	char	*value;
	size_t	start;
	size_t	len;

	start = tok->position;
	while (tok->input[tok->position] && 
		!is_space_tab(tok->input[tok->position]) && 
		!ms_is_special(tok->input[tok->position]) && 
		tok->input[tok->position] != '\'' && tok->input[tok->position] != '\"')
		tok->position++;
	len = tok->position - start;
	value = expand_tok(tok, start, len);
	if (!value)
		return (NULL);
	return (new_token(value, TOKEN_WORD));
}*/