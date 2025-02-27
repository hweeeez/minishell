/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 22:10:11 by hui-lim           #+#    #+#             */
/*   Updated: 2025/02/27 22:14:00 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	isredir(int type)
{
	if (type == TOKEN_REDIR_IN)
		return (1);
	if (type == TOKEN_REDIR_OUT)
		return (1);
	if (type == TOKEN_APPEND)
		return (1);
	if (type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

void	makeredir(t_node **newnode, t_token **token)
{
	t_redir	*redir;

	redir = (t_redir *)malloc(sizeof(t_redir));
	redir->type = (*token)->type;
	redir->file = ft_strdup((*token)->next->value);
	redir->next = NULL;
	if ((*newnode)->redirs == NULL)
	{
		(*newnode)->redirs = redir;
		(*newnode)->rootredir = redir;
	}
	else
	{
		(*newnode)->redirs->next = redir;
		(*newnode)->redirs = (*newnode)->redirs->next;
	}
	(*token) = (*token)->next;
}

int	handle_redirout(t_redir *re, t_exe **x, t_shell **s)
{
	closeput(-1, (*x)->puts[1]);
	if (check_dir_exists(re->file) == 0)
		return (filenotexisterr(re->file, s), 1);
	if (access(re->file, F_OK) == 0 && access(re->file, W_OK) == -1)
		return (permissiondeniederr(re->file, s), 1);
	(*x)->puts[1] = open(re->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	return (0);
}

void	filenotexisterr(char *file, t_shell **shell)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	(*shell)->exit_status = 1;
}

void	permissiondeniederr(char *file, t_shell **shell)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	(*shell)->exit_status = 1;
}
