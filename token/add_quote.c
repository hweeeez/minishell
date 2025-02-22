/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:35:11 by myuen             #+#    #+#             */
/*   Updated: 2025/02/22 21:08:30 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_quotes_to_value(t_token *token)
{
	size_t	old_len;
	char	*new_value;

	old_len = ft_strlen(token->value);
	new_value = malloc(old_len + 3);
	if (!new_value)
		return;
	new_value[0] = '\'';
	ft_memcpy(new_value + 1, token->value, old_len);
	new_value[old_len + 1] = '\'';
	new_value[old_len + 2] = '\0';
	free(token->value);
	token->value = new_value;
}

void	add_quotes_to_heredoc_tokens(t_token *head)
{
	t_token	*prev;
	t_token	*curr;

	prev = NULL;
	curr = head;
	while (curr != NULL)
	{
		if (curr->type == TOKEN_WORD && curr->hdquote == 1 && \
			prev && prev->type == TOKEN_HEREDOC)
		{
			add_quotes_to_value(curr);
		}
		prev = curr;
		curr = curr->next;
	}
}

char	*trim_char(const char *str, char c)
{
	size_t	len;
	char	*new_str;

	if (!str)
		return NULL;
	len = ft_strlen(str);
	if (len < 2 || str[0] != c || str[len - 1] != c)
		return ft_strdup(str);
	new_str = malloc(len - 1);
	if (!new_str)
		return NULL;
	ft_memcpy(new_str, str + 1, len - 2);
	new_str[len - 2] = '\0';
	return new_str;
}
