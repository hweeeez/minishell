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
		token = new_token(*current_word, TOKEN_WORD, tok->word_split);
		tok->word_split = 0;
		tok->position++;
		return (token);
	}
	tok->position++;
	return (NULL);
}

static void	handle_quotes(t_tokenizer *tok, char quote_type)
{
	tok->quote = quote_type;
	tok->position++;
}

static t_token	*handle_special(t_tokenizer *tok, char **current_word)
{
	t_token	*token;

	if (ft_strlen(*current_word))
	{
		token = new_token(*current_word, TOKEN_WORD, tok->word_split);
		tok->word_split = 0;
		return (token);
	}
	return (free(*current_word), handle_special_token(tok));
}

static void	handle_expansion(t_tokenizer *tok, t_shell *shell,
	char **current_word)
{
	char	*expanded;

	expanded = expand(tok, shell);
	if (expanded)
		*current_word = ft_strjoin_free(*current_word, expanded);
}

t_token	*process_no_quote(t_tokenizer *tok, t_shell *shell, char c, \
	char **current_word)
{
	if (ft_isspace(c))
		return (handle_space(tok, current_word));
	if (c == '\'')
	{
		handle_quotes(tok, '\'');
		return (NULL);
	}
	if (c == '"')
	{
		handle_quotes(tok, '"');
		return (NULL);
	}
	if (ms_is_special(c))
		return (handle_special(tok, current_word));
	if (c == '$')
	{
		tok->word_split = 1;
		handle_expansion(tok, shell, current_word);
		return (NULL);
	}
	*current_word = ft_strjoin_free(*current_word, ft_chartostr(c));
	tok->position++;
	return (NULL);
}
// t_token	*handle_word_token(t_tokenizer *tok)
// {
// 	char	*value;
// 	size_t	start;
// 	size_t	len;

// 	start = tok->position;
// 	while (tok->input[tok->position] && 
// 		!is_space_tab(tok->input[tok->position]) && 
// 		!ms_is_special(tok->input[tok->position]) && 
// 		tok->input[tok->position] != '\'' && tok->input[tok->position] != '\"')
// 		tok->position++;
// 	len = tok->position - start;
// 	value = expand_tok(tok, start, len);
// 	if (!value)
// 		return (NULL);
// 	return (new_token(value, TOKEN_WORD));
// }
