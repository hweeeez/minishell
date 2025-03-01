/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:19:58 by hui-lim           #+#    #+#             */
/*   Updated: 2025/01/29 17:20:00 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_redirin(t_redir *re, t_exe **x, t_shell **shell)
{
	closeput((*x)->puts[0], -1);
	if (access(re->file, F_OK) == -1)
		return (filenotexisterr(re->file, shell), 1);
	else if (access(re->file, F_OK | R_OK) == -1)
		return (permissiondeniederr(re->file, shell), 1);
	(*x)->puts[0] = open(re->file, O_RDONLY, 0644);
	return (0);
}

static int	handle_redirappend(t_redir *re, t_exe **x, t_shell **shell)
{
	closeput(-1, (*x)->puts[1]);
	if (access(re->file, F_OK) == 0 && access(re->file, W_OK) == -1)
		return (permissiondeniederr(re->file, shell), 1);
	(*x)->puts[1] = open(re->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	return (0);
}

void	closeput(int input, int output)
{
	if (input > -1 && input != STDIN_FILENO)
		close(input);
	if (output > -1 && output != STDOUT_FILENO)
		close(output);
}

static int	handle_hd(t_redir *re, t_exe **x, t_shell **shell, t_exebox **con)
{
	int	hd;

	hd = 0;
	closeput((*x)->puts[0], -1);
	hd = ft_heredoc(re, shell);
	if (hd == -1 || hd == 130)
		return (130);
	(*x)->puts[0] = open(HEREDOC_FILE, O_RDONLY, 0644);
	(*con)->skipnl = 1;
	return (1);
}

int	get_redir(t_redir *re, t_exe **x, t_shell **shell, t_exebox **con)
{
	if (re != NULL)
	{
		if (re->type == TOKEN_REDIR_OUT)
		{
			if (handle_redirout(re, x, shell) == 1)
				return (1);
		}
		else if (re->type == TOKEN_APPEND)
		{
			if (handle_redirappend(re, x, shell) == 1)
				return (1);
		}
		else if (re->type == TOKEN_REDIR_IN)
		{
			if (handle_redirin(re, x, shell) == 1)
				return (1);
		}
		else if (re->type == TOKEN_HEREDOC)
		{
			if (handle_hd(re, x, shell, con) == 130)
				return (130);
		}
		return (get_redir(re->next, x, shell, con));
	}
	return (0);
}
