/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_builtin_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:27:53 by myuen             #+#    #+#             */
/*   Updated: 2025/02/19 19:28:05 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exitchild(t_shell **shell, int exitcode, t_sigs **sigs, t_exe **exe)
{
	(*shell)->exit_status = exitcode;
	free(*sigs);
	free(*exe);
	ft_exit(shell, NULL);
}

//builtins need to write to stdout, but do not read from stdin (but we should still dup2)
int	do_execution(t_shell **shell, char **cmd, t_sigs **sigs, t_exe **exe)
{
	int	builtinvalue;
	char	*command;

	if (cmd == NULL)
		exitchild(shell, 0, sigs, exe);
	builtinvalue = checkif_builtin(shell, cmd);
	if (builtinvalue == -1)
	{
		if (execve(cmd[0], cmd, (*shell)->env) == -1)
		{
			command = ft_find_cmd_path(cmd[0], &cmd, (*shell)->env);
			if (command == NULL)
				exitchild(shell, 127, sigs, exe);
			else
				free(command);
			exitchild(shell, errno, sigs, exe);
		}
	}
	exitchild(shell, 0, sigs, exe);
	return (1);
}

int	checkif_builtin(t_shell **shell, char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 1)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd[0], "cd") == 1)
		return (ft_cd(*shell, cmd));
	if (ft_strcmp(cmd[0], "pwd") == 1)
		return (ft_pwd());
	if (ft_strcmp(cmd[0], "export") == 1)
		return (ft_export(*shell, cmd));
	if (ft_strcmp(cmd[0], "unset") == 1)
		return (ft_unset(*shell, cmd));
	if (ft_strcmp(cmd[0], "env") == 1)
		return (ft_env(*shell));
	if (ft_strcmp(cmd[0], "exit") == 1)
		return (ft_exit(shell, cmd));
	if (ft_strcmp(cmd[0], ".") == 1)
		return (ft_dot(cmd));
	if (ft_strcmp(cmd[0], "..") == 1)
		return (ft_dotdot());
	return (-1);
}

