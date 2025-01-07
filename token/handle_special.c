/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 20:33:51 by myuen             #+#    #+#             */
/*   Updated: 2024/12/18 20:57:19 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token_type	determine_token_type(char c, char next, size_t *extra_pos)
{
	if (c == '|')
		return (TOKEN_PIPE);
	if (c == '<' && next == '<')
	{
		*extra_pos = 1;
		return (TOKEN_HEREDOC);
	}
	if (c == '>' && next == '>')
	{
		*extra_pos = 1;
		return (TOKEN_APPEND);
	}
	if (c == '<')
		return (TOKEN_REDIR_IN);
	if (c == '>')
		return (TOKEN_REDIR_OUT);
	return (TOKEN_ERROR);
}

static char	*create_token_value(char c, t_token_type type)
{
	char	*value;

	value = (char *)malloc(3);
	if (!value)
		return (NULL);
	value[0] = c;
	if (type == TOKEN_HEREDOC || type == TOKEN_APPEND)
		value[1] = c;
	else
		value[1] = '\0';
	value[2] = '\0';
	return (value);
}

t_token	*handle_special(t_tokenizer *tok)
{
	char			c;
	char			next;
	char			*value;
	t_token_type	type;
	size_t			extra_pos;

	c = tok->input[tok->position];
	next = tok->input[tok->position + 1];
	extra_pos = 0;
	type = determine_token_type(c, next, &extra_pos);
	tok->position += extra_pos;
	value = create_token_value(c, type);
	if (!value)
		return (NULL);
	tok->position++;
	return (new_token(value, type));
}