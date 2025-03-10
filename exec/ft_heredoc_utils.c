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

// int	ft_heredoc(t_redir *redirs, t_shell **shell)
// {
// 	char	*temp;

// 	if (redirs->file[0] == '\'')
// 	{
// 		temp = redirs->file;
// 		redirs->file = trim_char(redirs->file, '\'');
// 		free(temp);
// 		(*shell)->expand_flag = 0;
// 		return (ft_heredoc_exe(redirs, shell));
// 	}
// 	else
// 	{
// 		(*shell)->expand_flag = 1;
// 		return (ft_heredoc_exe(redirs, shell));
// 	}
// }

int	ft_heredoc(t_redir *redirs, t_shell **shell)
{
	char	*temp;
	int		first_char_quote;
	int		last_char_quote;
	size_t	len;

	if (!redirs->file)
		return (ft_heredoc_exe(redirs, shell));
	len = ft_strlen(redirs->file);
	first_char_quote = (len > 0 && redirs->file[0] == '\'');
	last_char_quote = (len > 1 && redirs->file[len - 1] == '\'');
	if (first_char_quote && last_char_quote)
	{
		temp = redirs->file;
		redirs->file = trim_char(redirs->file, '\'');
		free(temp);
		(*shell)->expand_flag = 0;
	}
	else
	{
		(*shell)->expand_flag = 1;
	}
	return (ft_heredoc_exe(redirs, shell));
}

void	handle_sigint(int filefd, t_shell **shell)
{
	close(filefd);
	unlink(HEREDOC_FILE);
	(*shell)->exit_status = 130;
}

void	handle_eof(int filefd)
{
	ft_putstr_fd("warning: heredoc delimited by end-of-file\n", 2);
	close(filefd);
}
