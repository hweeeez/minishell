/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:16:32 by hui-lim           #+#    #+#             */
/*   Updated: 2025/01/30 16:16:34 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_heredoc(t_redir *redirs, t_shell **shell)
{
	char	*temp;

	if (redirs->file[0] == '\'')
	{
		temp = redirs->file;
		redirs->file = trim_char(redirs->file, '\'');
		free(temp);
		return (ft_heredoc_exe(redirs, shell, 0));
	}
	else
	{
		return (ft_heredoc_exe(redirs, shell, 1));
	}
}
