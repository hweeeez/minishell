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

static int	is_redirection_token(t_token_type type)
{
	return (type == TOKEN_REDIR_IN || type == TOKEN_REDIR_OUT || \
			type == TOKEN_APPEND || type == TOKEN_HEREDOC);
}

static int	check_redirection_error(t_token *current)
{
	if (!current->next)
		return (print_error("syntax error: unexpected token near 'newline'\n"));
	if (current->type == TOKEN_HEREDOC)
	{
		if (current->next->type != TOKEN_WORD)
			return (print_error("syntax error: unexpected token after '<<'\n"));
		if (current->next->value == NULL)
			return (0);
	}
	else if (is_redirection_token(current->type))
	{
		if (current->next->type == TOKEN_PIPE)
			return (print_error("syntax error: unexpected token near '|'\n"));
		if (is_redirection_token(current->next->type))
			return (print_error("syntax error: unexpected token near '>'\n"));
		if (current->next->type != TOKEN_WORD)
			return (print_error("syntax error: unexpected token\n"));
		if (!is_valid_filename(current->next->value))
			return (print_error("syntax error: invalid filename\n"));
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
		return (print_error("syntax error : unexpected token near `|'\n"));
	prev = NULL;
	current = head;
	while (current)
	{
		if (current->type == TOKEN_PIPE && \
			(!prev || !current->next || current->next->type == TOKEN_PIPE))
			return (print_error("syntax error : unexpected token near `|'\n"));
		if (is_redirection_token(current->type))
		{
			if (check_redirection_error(current))
				return (1);
		}
		prev = current;
		current = current->next;
	}
	return (0);
}

// static int	check_redirection_error(t_token *current)
// {
// 	if (!current->next)
// 		return (print_error("syntax error : unexpected token `newline'\n"));
// 	if (current->next->type != TOKEN_WORD)
// 	{
// 		if (current->next->type == TOKEN_PIPE)
// 			return (print_error("syntax error : unexpected token `|'\n"));
// 		else if (is_redirection_token(current->next->type))
// 			return (print_error("syntax error : unexpected token `>'\n"));
// 		else
// 			return (print_error("syntax error : unexpected token\n"));
// 	}
// 	return (0);
// }
// int is_valid_filename(char *str)
// {
// 	struct stat path_stat;
// 	if (!str || *str == '\0')
// 		return (1);
// 	if (ft_strncmp(str, ".", 2) == 0 || ft_strncmp(str, "..", 3) == 0)
// 		return (0);
// 	if (stat(str, &path_stat) == 0 && ((path_stat.st_mode & S_IFMT) == S_IFDIR))
// 		return (0);
// 	return (1);
// }