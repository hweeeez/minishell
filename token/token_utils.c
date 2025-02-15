/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2025/01/29 18:29:08 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_tokenizer(t_tokenizer *tok, const char *input, t_shell *shell)
{
	tok->input = input;
	tok->position = 0;
	tok->quote = '0';
	tok->error = 0;
	tok->shell = shell;
	tok->shell = 0;
}

int	is_space_tab(char c)
{
	return (c == ' ' || c == '\t');
}

int	ms_is_special(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

void	skip_whitespace(t_tokenizer *tok)
{
	if (!tok->input)
		return;
	while (tok->input[tok->position] && \
				ft_isspace(tok->input[tok->position]))
		tok->position++;
}
