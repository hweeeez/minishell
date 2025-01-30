/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 19:35:11 by myuen             #+#    #+#             */
/*   Updated: 2025/01/30 19:41:43 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	validate_token_syntax(t_token *head)
{
	t_token	*current;
	t_token	*prev;

	if (!head)
		return (0);
	if (head->type == TOKEN_PIPE)
		return (print_error("syntax error near unexpected token `|'"));
	prev = NULL;
	current = head;
	while (current)
	{
		if (current->type == TOKEN_PIPE)
		{
			if (!prev || !current->next || current->next->type == TOKEN_PIPE)
				return (print_error("syntax error near unexpected token `|'"));
		}
		else if (is_redirection_token(current->type))
		{
			if (!current->next)
				return (print_error("syntax error near unexpected token `newline'"));
			if (current->next->type != TOKEN_WORD)
			{
				if (current->next->type == TOKEN_PIPE)
					return (print_error("syntax error near unexpected token `|'"));
				else if (is_redirection_token(current->next->type))
					return (print_error("syntax error near unexpected token `>'")); // More generic for redirections
				else
					return (print_error("syntax error near unexpected token `%s'", current->next->value)); // Print the actual token value
			}
		}
		prev = current; // Move prev to current for the next iteration
		current = current->next;
	}
	return (0);
}

// Helper function to check if a token type is a redirection token
int	is_redirection_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT || \
			type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

// Assuming you have a print_error function like this (or adapt to your error handling)
int	print_error(const char *format, ...)
{
	va_list args;

	fprintf(stderr, "minishell: "); // Standard error output prefix
	va_start(args, format);
	vfprintf(stderr, format, args);
	va_end(args);
	fprintf(stderr, "\n");
	return (1); // Indicate error
}
