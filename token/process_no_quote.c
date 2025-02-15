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
		token = new_token(*current_word, TOKEN_WORD);
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
		token = new_token(*current_word, TOKEN_WORD);
		return (token);
	}
	tok->position++;
	return (free(*current_word), handle_special_token(tok));
}

// static void	handle_expansion(t_tokenizer *tok, t_shell *shell,
// 	char **current_word)
// {
// 	char	*expanded;

// 	expanded = expand_split(tok, shell);
// 	if (expanded)
// 		*current_word = ft_strjoin_free(*current_word, expanded);
// }

static t_token	*handle_expansion(t_tokenizer *tok, t_shell *shell, char **current_word)
{
	//char	*expanded;
	t_token	*tokens;

	*current_word = ft_strjoin_free(*current_word, expand_split(tok, shell));
	printf("c_word: #%s#\n", *current_word);
	if (!*current_word)
		return (NULL);
	tokens = tokenize_expanded_string(*current_word);
	free(*current_word);
	*current_word = NULL;
	if (tokens)
	{
		return (tokens);
	}
	return (NULL);
}

t_token	*process_no_quote(t_tokenizer *tok, t_shell *shell, char c, \
	char **current_word)
{
	t_token	*token;

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
		token = handle_expansion(tok, shell, current_word);
		if (token)
			return (token);
		else
			return (NULL);
	}
	printf("no q #%c#\n", tok->input[tok->position]);
	*current_word = ft_strjoin_free(*current_word, ft_chartostr(c));
	printf("current word:#%s#\n", *current_word);
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
