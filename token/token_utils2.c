/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 16:58:32 by myuen             #+#    #+#             */
/*   Updated: 2025/02/27 18:28:28 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_type	last_token_type(t_token *head)
{
	if (!head)
		return (TOKEN_ERROR);
	while (head->next)
		head = head->next;
	return (head->type);
}

int	pre_is_heredoc(t_token *head)
{
	if (!head)
		return (0);
	while (head->next)
		head = head->next;
	return (head->type == TOKEN_HEREDOC);
}
