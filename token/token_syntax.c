/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:35:11 by myuen             #+#    #+#             */
/*   Updated: 2025/01/30 20:34:17 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_error(const char *format)
{
	ft_putstr_fd((char *)format, STDERR_FILENO);
	return (1);
}

int	is_redirection_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT || \
			type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

static int	check_redirection_error(t_token *current)
{
	if (!current->next)
		return (print_error("syntax error : unexpected token `newline'\n"));
	if (current->next->type != TOKEN_WORD)
	{
		if (current->next->type == TOKEN_PIPE)
			return (print_error("syntax error : unexpected token `|'\n"));
		else if (is_redirection_token(current->next->type))
			return (print_error("syntax error : unexpected token `>'\n"));
		else
			return (print_error("syntax error : unexpected token\n"));
	}
	return (0);
}

int	validate_token_syntax(t_token *head)
{
	t_token	*current;
	t_token	*prev;

	if (!head)
		return (0);
	if (head->type == TOKEN_PIPE)
		return (print_error("syntax error : unexpected token `|'\n"));
	prev = NULL;
	current = head;
	while (current)
	{
		if (current->type == TOKEN_PIPE && \
			(!prev || !current->next || current->next->type == TOKEN_PIPE))
			return (print_error("syntax error : unexpected token `|'\n"));
		else if (is_redirection_token(current->type) && \
			check_redirection_error(current))
			return (1);
		prev = current;
		current = current->next;
	}
	return (0);
}
