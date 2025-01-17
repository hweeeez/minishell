/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2025/01/17 19:10:49 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_tokenizer(t_tokenizer *tok, const char *input, t_shell *shell)
{
	tok->input = input;
	tok->position = 0;
	tok->quote = 0;
	tok->error = 0;
	tok->shell = shell;
}

int	ms_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	ms_is_special(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	skip_whitespace(t_tokenizer *tok)
{
	while (tok->input[tok->position] && \
				ms_is_whitespace(tok->input[tok->position]))
		tok->position++;
}
