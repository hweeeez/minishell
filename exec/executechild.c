/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executechild.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:39:36 by hui-lim           #+#    #+#             */
/*   Updated: 2025/02/27 21:41:35 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dup_og(int *og_stdout, int *og_stdin)
{
	*og_stdout = dup(STDOUT_FILENO);
	*og_stdin = dup(STDIN_FILENO);
	if (*og_stdin == -1 || *og_stdout == -1)
		return (-1);
	return (0);
}

static void	close_pipefds(t_exe *exe, t_node *node)
{
	if (node->right == NULL)
	{
		if ((exe)->pipefd[0] > -1)
			close((exe)->pipefd[0]);
		if ((exe)->pipefd[1] > -1)
			close((exe)->pipefd[1]);
	}
}

void	executechild(t_node *node, t_exebox **con, t_shell **shell)
{
	t_exe	*exe;

	exe = (*con)->exes[(*con)->numpid - 1];
	if ((exe)->puts[0] != STDIN_FILENO)
	{
		dup_fd(exe, 1);
		close_pipefds(exe, node);
	}
	if ((exe)->puts[1] != STDOUT_FILENO)
	{
		dup_fd(exe, 2);
		close_pipefds(exe, node);
	}
	else if (node->right != NULL)
	{
		if ((exe)->pipefd[0] > -1)
			close((exe)->pipefd[0]);
		dup2(exe->pipefd[1], STDOUT_FILENO);
		if ((exe)->pipefd[1] > -1)
			close(exe->pipefd[1]);
	}
	do_execution(shell, node->left->args, con);
}
