/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:53:25 by myuen             #+#    #+#             */
/*   Updated: 2025/01/16 18:38:07 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	find_quote_end(t_tokenizer *tok, char quote)
{
	size_t	start;

	start = tok->position;
	tok->position++;
	while (tok->input[tok->position] && tok->input[tok->position] != quote)
		tok->position++;
	return (start);
}

static size_t	get_quote_length(t_tokenizer *tok, size_t start)
{
	size_t	len;

	if (!tok->input[tok->position])
	{
		tok->error = 1;
		len = tok->position - start;
	}
	else
	{
		len = tok->position - start + 1;
		tok->position++;
	}
	return (len);
}

static char	*allocate_quote(t_tokenizer *tok, size_t start, size_t len)
{
	char	*value;

	value = (char *)malloc(len + 1 - 2);
	if (!value)
		return (NULL);
	ft_strlcpy(value, tok->input + start + 1, len - 1);
	return (value);
}

char	*handle_quote(t_tokenizer *tok)
{
	size_t	start;
	size_t	len;

	tok->quote = tok->input[tok->position];
	start = find_quote_end(tok, tok->quote);
	len = get_quote_length(tok, start);
	if (tok->error)
		return (NULL);
	return (allocate_quote(tok, start, len));
}
