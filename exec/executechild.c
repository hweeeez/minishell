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

int	checkif_builtin(t_shell **shell, char **cmd, t_exebox **exe)
{
	if (ft_strcmp(cmd[0], "echo") == 1)
		return ((*exe)->isbuiltin = 1, (*shell)->exit_status = ft_echo(cmd));
	if (ft_strcmp(cmd[0], "cd") == 1)
		return ((*exe)->isbuiltin = 1, \
		(*shell)->exit_status = ft_cd(*shell, cmd));
	if (ft_strcmp(cmd[0], "pwd") == 1)
		return ((*exe)->isbuiltin = 1, (*shell)->exit_status = ft_pwd());
	if (ft_strcmp(cmd[0], "export") == 1)
		return ((*exe)->isbuiltin = 1, \
		(*shell)->exit_status = ft_export(*shell, cmd));
	if (ft_strcmp(cmd[0], "unset") == 1)
		return ((*exe)->isbuiltin = 1, \
		(*shell)->exit_status = ft_unset(*shell, cmd));
	if (ft_strcmp(cmd[0], "env") == 1)
		return ((*exe)->isbuiltin = 1, (*shell)->exit_status = ft_env(*shell));
	if (ft_strcmp(cmd[0], "exit") == 1)
		return ((*exe)->isbuiltin = 1, ft_exit(shell, cmd, exe));
	if (ft_strcmp(cmd[0], ".") == 1)
		return ((*exe)->isbuiltin = 1, (*shell)->exit_status = ft_dot(cmd));
	if (ft_strcmp(cmd[0], "..") == 1)
		return ((*exe)->isbuiltin = 1, (*shell)->exit_status = ft_dotdot());
	return (-1);
}

int	dup_og(int *og_stdout, int *og_stdin)
{
	*og_stdout = dup(STDOUT_FILENO);
	*og_stdin = dup(STDIN_FILENO);
	if (*og_stdin == -1 || *og_stdout == -1)
		return (-1);
	return (0);
}

void	close_pipefds(t_exe *exe)
{
	if ((exe)->pipefd[0] > -1)
		close((exe)->pipefd[0]);
	if ((exe)->pipefd[1] > -1)
		close((exe)->pipefd[1]);
}

void	executechild(t_node *node, t_exebox **con, t_shell **shell)
{
	t_exe	*exe;

	exe = (*con)->exes[(*con)->numpid - 1];
	if ((exe)->puts[0] != STDIN_FILENO)
	{
		dup_fd(exe, 1);
		if (node->right == NULL)
			close_pipefds(exe);
	}
	if ((exe)->puts[1] != STDOUT_FILENO)
	{
		dup_fd(exe, 2);
		if (node->right == NULL)
			close_pipefds(exe);
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
