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
	t_node	*left;
	t_exe	*exe;

	left = node->left;
	input = STDIN_FILENO;
	if (node->type == 0)
	{
		if (checkif_builtin(left->args[0]) == 0)
		{
			if (left->rootredir != NULL)
			{
				if (left->rootredir->type == TOKEN_REDIR_IN)
				{
					input = get_redir(left->rootredir);
					left->redirs = left->rootredir->next;
				}
				else if (node->left->rootredir->type == TOKEN_HEREDOC)
					return (2);
			}
			else
				left->redirs = node->left->rootredir;
			initexenode(&exe, input);
			exe_commands(node, &exe, envp);
			free(exe);
		}
	}
	return (0);
}

void	initexenode(t_exe **exe, int input)
{
	(*exe) = (t_exe *)malloc(sizeof(t_exe));
	(*exe)->childpid = -1;
	(*exe)->pid = -1;
	(*exe)->puts[0] = input;
	(*exe)->puts[1] = STDOUT_FILENO;
}

int	exe_commands(t_node *node, t_exe **exe, char **envp)
{
	// pid_t	pid;
	// pid_t	child_pid;
	// int		pipefd[2];
	// int		puts[2];
	// int		status;
	t_sigs	*sigs;
	static int		flag = 0;
	t_exe	*childexe;
	int		pid;

	pid = (*exe)->pid;
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
	{
		close((*exe)->pipefd[1]);
		initexenode(&childexe, (*exe)->pipefd[0]);
		(*exe)->childpid = exe_commands(node->right, &childexe, envp);
		free(childexe);
	}
	wait_children(exe);
	free(sigs);
	return (pid);
}

void	closeputs(t_exe **exe)
{
	if ((*exe)->puts[0] != STDIN_FILENO)
		close((*exe)->puts[0]);
    if ((*exe)->puts[1] != STDOUT_FILENO)
		close((*exe)->puts[1]);
}

// int	exe_commands(t_node *node, int input, int output, char **envp)
// {
// 	pid_t	pid;
// 	pid_t	child_pid;
// 	int		pipefd[2];
// 	int		puts[2];
// 	int		status;
// 	t_sigs	*sigs;
// 	static int		flag = 0;

// 	init_exesigs(&sigs);
// 	child_pid = -1;
// 	if (node->right != NULL || node->left->redirs != NULL)
// 	{
// 		if (pipe(pipefd) == -1)
// 			return (-1);
// 	}
// 	pid = fork();
// 	puts[0] = input;
// 	puts[1] = output;
// 	if (pid == -1)
// 		return (-1);
// 	if (pid == 0)
// 	{
// 		do_sigaction(SIGQUIT, SIGINT, sigs);
// 		executechild(node, pipefd, puts, envp);
// 	}
// 	else if (pid > 0)
// 		sigaction(SIGINT, &(sigs->ignore), NULL);
// 	closeputs(input, output);
// 	if (node->right != NULL)
// 	{
// 		close(pipefd[1]);
// 		child_pid = exe_commands(node->right, pipefd[0], STDOUT_FILENO, envp);
// 		waitpid(pid, &status, 0);
// 		waitpid(child_pid, NULL, 0);
// 	}
// 	else
// 		waitpid(pid, &status, 0);
// 	ft_coredump_msg(status, &flag);
// 	return (pid);
// }

// void	closeputs(int input, int output)
// {
// 	if (input != STDIN_FILENO)
// 		close(input);
//     if (output != STDOUT_FILENO)
// 		close(output);
// }

void	executechild(t_node *node, t_exe **exe, char **envp)
{
	char	**c;

	if ((*exe)->puts[0] != STDIN_FILENO)
	{
		dup2((*exe)->puts[0], STDIN_FILENO);
		close((*exe)->puts[0]);
	}
	if (node->right != NULL)
	{
		close((*exe)->pipefd[0]);
		dup2((*exe)->pipefd[1], STDOUT_FILENO);
		close((*exe)->pipefd[1]);
	}
	else if (node->left->redirs != NULL)
	{
		int	filefd = get_redir(node->left->redirs);
		dup2(filefd, STDOUT_FILENO);
		close(filefd);
	}
	c = node->left->args;
	if (execve(c[0], c, envp) == -1)
	{	
		printf("Command not found!\n");
		exit(0);
	}
}

int checkif_builtin(char* cmd)
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
