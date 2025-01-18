/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 19:53:25 by myuen             #+#    #+#             */
/*   Updated: 2025/01/18 18:48:50 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*handle_word_token(t_tokenizer *tok)
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
