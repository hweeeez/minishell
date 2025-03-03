/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_quote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:53:25 by myuen             #+#    #+#             */
/*   Updated: 2025/01/30 18:59:31 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*process_double_quote(t_tokenizer *tok, t_shell *shell,
	char c, char **current_word)
{
	char	*expanded;

	if (c == '"')
	{
		tok->quote = '0';
		tok->position++;
	}
	else if (c == '$' && !pre_is_heredoc(shell->token))
	{
		expanded = expand(tok, shell);
		if (expanded)
		{
			*current_word = ft_strjoin_free(*current_word, expanded);
		}
	}
	else
	{
		*current_word = ft_strjoin_free(*current_word, ft_chartostr(c));
		tok->position++;
	}
	return (NULL);
}

t_token	*process_single_quote(t_tokenizer *tok, char c, char **current_word)
{
	if (c == '\'')
	{
		tok->quote = '0';
		tok->position++;
	}
	else
	{
		*current_word = ft_strjoin_free(*current_word, ft_chartostr(c));
		tok->position++;
	}
	return (NULL);
}

// static size_t	find_quote_end(t_tokenizer *tok, char quote)
// {
// 	size_t	start;

// 	start = tok->position;
// 	tok->position++;
// 	while (tok->input[tok->position] && tok->input[tok->position] != quote)
// 		tok->position++;
// 	return (start);
// }

// static size_t	get_quote_length(t_tokenizer *tok, size_t start)
// {
// 	size_t	len;

// 	if (!tok->input[tok->position])
// 	{
// 		tok->error = 1;
// 		len = tok->position - start;
// 	}
// 	else
// 	{
// 		len = tok->position - start + 1;
// 		tok->position++;
// 	}
// 	return (len);
// }

// static char	*allocate_quote(t_tokenizer *tok, size_t start, size_t len)
// {
// 	char	*value;

// 	value = (char *)malloc(len + 1 - 2);
// 	if (!value)
// 		return (NULL);
// 	ft_strlcpy(value, tok->input + start + 1, len - 1);
// 	return (value);
// }

// static char	*expand_quote(t_tokenizer *tok, char *value)
// {
// 	char	*expanded;
// 	size_t	len;

// 	if (!value || tok->quote == '\'')
// 		return (value);
// 	len = ft_strlen(value);
// 	expanded = expand_tok(tok, tok->position - len - 1, len);
// 	free(value);
// 	return (expanded);
// }

// char	*handle_quote(t_tokenizer *tok)
// {
// 	size_t	start;
// 	size_t	len;
// 	char	*value;

// 	tok->quote = tok->input[tok->position];
// 	start = find_quote_end(tok, tok->quote);
// 	len = get_quote_length(tok, start);
// 	if (tok->error)
// 		return (NULL);
// 	value = allocate_quote(tok, start, len);
// 	if (!value)
// 		return (NULL);
// 	return (expand_quote(tok, value));
// }
