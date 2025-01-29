/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traversetree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:11:22 by hui-lim           #+#    #+#             */
/*   Updated: 2025/01/14 21:11:24 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] != '\0')
	{
		if (str1[i] != str2[i] || str2[i] == '\0')
			return (-1);
		i++;
	}
	return (1);
}

int	execute(t_node *node, char **envp)
{
	int		input;
	int		output;
	t_node	*left;
	t_exe	*exe;

	left = node->left;
	input = STDIN_FILENO;
	output = STDOUT_FILENO;
	if (node->type == 0)
	{
		if (checkif_builtin(left->args[0]) == 0)
		{
			initexenode(&exe);
			exe_commands(node, &exe, envp);
			free(exe);
		}
	}
	return (0);
}

int	exe_commands(t_node *node, t_exe **exe, char **envp)
{
	t_sigs	*sigs;

	init_exesigs(&sigs);
	if (node->right != NULL || node->left->redirs != NULL)
	{
		if (pipe((*exe)->pipefd) == -1)
			return (-1);
	}
	(*exe)->pid = fork();
	if ((*exe)->pid == -1)
		return (-1);
	if ((*exe)->pid == 0)
	{
		do_sigaction(SIGQUIT, SIGINT, sigs);
		executechild(node, exe, envp);
	}
	else if ((*exe)->pid > 0)
		sigaction(SIGINT, &(sigs->ignore), NULL);
	closeputs(exe);
	if (node->right != NULL)
		exe_rightnode(exe, node->right, envp);
	wait_children(exe);
	free(sigs);
	return ((*exe)->pid);
}

void	executechild(t_node *node, t_exe **exe, char **envp)
{
	char	**c;

	has_redir(exe, node);
	if ((*exe)->puts[0] != STDIN_FILENO)
	{
		dup2((*exe)->puts[0], STDIN_FILENO);
		close((*exe)->puts[0]);
	}
	if ((*exe)->puts[1] != STDOUT_FILENO)
	{
		dup2((*exe)->puts[1], STDOUT_FILENO);
		close((*exe)->puts[1]);
	}
	else if (node->right != NULL)
	{
		close((*exe)->pipefd[0]);
		dup2((*exe)->pipefd[1], STDOUT_FILENO);
		close((*exe)->pipefd[1]);
	}
	c = node->left->args;
	if (execve(c[0], c, envp) == -1)
	{	
		printf("Command not found!\n");
		exit(0);
	}
}

int	checkif_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 1)
		return ((printf("%s\n", "run echo")), 1);
	if (ft_strcmp(cmd, "cd") == 1)
		return (printf("%s\n", "run cd"), 1);
	if (ft_strcmp(cmd, "pwd") == 1)
		return (get_pwd(), 1);
	if (ft_strcmp(cmd, "export") == 1)
		return (printf("%s\n", "run export"), 1);
	if (ft_strcmp(cmd, "unset") == 1)
		return (printf("%s\n", "run unset"), 1);
	if (ft_strcmp(cmd, "env") == 1)
		return (printf("%s\n", "run env"), 1);
	if (ft_strcmp(cmd, "exit") == 1)
		return (printf("%s\n", "run exit"), 1);
	return (0);
}
