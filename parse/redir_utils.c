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

static void	filenotexisterr(char *file, t_shell **shell)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	(*shell)->exit_status = 1;
}

static void	permissiondeniederr(char *file, t_shell **shell)
{
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Permission denied\n", 2);
	(*shell)->exit_status = 1;
}

static void	closeput(int input, int output)
{
	if (input > -1 && input != STDIN_FILENO)
		close(input);
	if (output > -1 && output != STDOUT_FILENO)
		close(output);
}

int	get_redir(t_redir *re, t_exe **x, t_shell **shell)
{
	int	hd;

	hd = 0;
	if (re != NULL)
	{
		if (re->type == TOKEN_REDIR_OUT)
		{
			closeput(-1, (*x)->puts[1]);
			if (check_dir_exists(re->file) == 0)
				return (filenotexisterr(re->file, shell), 1);
			if (access(re->file, F_OK) == 0 && access(re->file, W_OK) == -1)
				return (permissiondeniederr(re->file, shell), 1);
			(*x)->puts[1] = open(re->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		}
		else if (re->type == TOKEN_APPEND)
		{
			closeput(-1, (*x)->puts[1]);
			if (access(re->file, F_OK) == 0 && access(re->file, W_OK) == -1)
				return (permissiondeniederr(re->file, shell), 1);
			(*x)->puts[1] = open(re->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		}
		else if (re->type == TOKEN_REDIR_IN)
		{
			closeput((*x)->puts[0], -1);
			if (access(re->file, F_OK | R_OK) == -1)
				return (filenotexisterr(re->file, shell), 1);
			(*x)->puts[0] = open(re->file, O_RDONLY, 0644);
		}
		else if (re->type == TOKEN_HEREDOC)
		{
			closeput((*x)->puts[0], -1);
			hd = ft_heredoc(re, shell);
			if (hd == -1 || hd == 130)
				return(130);
			(*x)->puts[0] = open(HEREDOC_FILE, O_RDONLY, 0644);
		}
		return (get_redir(re->next, x, shell));
	}
	return (0);
}

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
