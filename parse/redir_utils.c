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

static int	handle_redirin(t_redir *re, t_exe **x, t_shell **s, t_exebox **box)
{
	closeput((*x)->puts[0], -1);
	if (access(re->file, F_OK) == -1)
		return (filenotexisterr(re->file, s), 1);
	else if (access(re->file, F_OK | R_OK) == -1)
		return ((*x)->puts[0] = STDIN_FILENO, permdenied(re->file, s), 1);
	(*x)->puts[0] = open(re->file, O_RDONLY, 0644);
	if ((*x)->puts[0] == -1)
		return (ft_exit(s, NULL, box), 1);
	return (0);
}

static int	handle_redirapp(t_redir *re, t_exe **x, t_shell **s, t_exebox **b)
{
	closeput(-1, (*x)->puts[1]);
	if (access(re->file, F_OK) == 0 && access(re->file, W_OK) == -1)
		return ((*x)->puts[1] = STDOUT_FILENO, permdenied(re->file, s), 1);
	(*x)->puts[1] = open(re->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if ((*x)->puts[1] == -1)
		return (ft_exit(s, NULL, b), 1);
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
		return (unlink(HEREDOC_FILE), 130);
	(*x)->puts[0] = open(HEREDOC_FILE, O_RDONLY, 0644);
	if ((*x)->puts[0] == -1)
		return (ft_exit(shell, NULL, con), 1);
	if (con != NULL && *con != NULL)
		(*con)->skipnl = 1;
	return (0);
}

int	get_redir(t_redir *re, t_exe **x, t_shell **shell, t_exebox **con)
{
	int	ret;

	if (re == NULL)
		return (0);
	if (re->type == TOKEN_REDIR_OUT)
		ret = handle_redirout(re, x, shell, con);
	else if (re->type == TOKEN_APPEND)
		ret = handle_redirapp(re, x, shell, con);
	else if (re->type == TOKEN_REDIR_IN)
		ret = handle_redirin(re, x, shell, con);
	else if (re->type == TOKEN_HEREDOC)
		ret = handle_hd(re, x, shell, con);
	else
		ret = 0;
	if (ret != 0)
		return (ret);
	return (get_redir(re->next, x, shell, con));
}
