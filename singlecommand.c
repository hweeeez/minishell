/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   singlecommand.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/30 20:06:01 by hui-lim           #+#    #+#             */
/*   Updated: 2024/12/30 20:06:08 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exe_single(t_node *node, char **envp)
{
	pid_t	pid;
	char	**c;

	if (!node)
		return (-1);
	pid = fork();
	if (pid == -1)
		return (-1);
	if (pid == 0)
	{
		c = node->left->args;
		if (execve(c[0], c, envp) == -1)
			printf("%s\n Error", c[0]);
	}
	waitpid(pid, NULL, 0);
	return (pid);
}

if (puts[0] != STDIN_FILENO)
	{
		dup2(puts[0], STDIN_FILENO);
		close(puts[0]);
	}
	if (node->right != NULL)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else if (node->left->redirections != NULL)
	{
		int	filefd = open(node->left->redirections->file, O_WRONLY | O_CREAT, 0644);
		dup2(puts[1], filefd);
		close(puts[1]);
	}
	if (node->left != NULL)
		c = node->left->args;
	else
		c = node->args;
	if (execve(c[0], c, envp) == -1)
		printf("%s\n Error", c[0]);
