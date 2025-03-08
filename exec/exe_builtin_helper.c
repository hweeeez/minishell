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

void	free_exe(t_exebox **exe)
{
	int	i;

	i = 0;
	if (*exe == NULL)
		return ;
	if ((*exe)->pids != NULL)
	{
		free((*exe)->pids);
		(*exe)->pids = NULL;
	}
	while (i < (*exe)->numpid)
	{
		if ((*exe)->exes[i] != NULL)
			free((*exe)->exes[i]);
		if ((*exe)->sigs != NULL)
			free((*exe)->sigs[i]);
		i++;
	}
	if ((*exe)->numpid == 0 && (*exe)->isbuiltin != 1)
		free((*exe)->exes[0]);
	free((*exe)->exes);
	free((*exe)->sigs);
	free(*exe);
	*exe = NULL;
}

static void	exitchild(t_shell **shell, int exitcode, t_exebox **exe)
{
	(*shell)->exit_status = exitcode;
	ft_exit(shell, NULL, exe);
}

int	do_execution(t_shell **shell, char **cmd, t_exebox **exe)
{
	int		builtinvalue;
	char	*command;

	if (cmd == NULL)
		exitchild(shell, 0, exe);
	builtinvalue = checkif_builtin(shell, cmd, exe);
	if (builtinvalue == -1)
	{
		if (execve(cmd[0], cmd, (*shell)->env) == -1)
		{
			command = ft_find_cmd_path(cmd[0], &cmd, (*shell)->env);
			if (command == NULL)
				exitchild(shell, 127, exe);
			else
				free(command);
			exitchild(shell, errno, exe);
		}
	}
	exitchild(shell, 0, exe);
	return (1);
}

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

void	initexecontainer(t_exebox **con)
{
	(*con) = (t_exebox *)malloc(sizeof(t_exebox));
	if ((*con) == NULL)
		memerr_exit(1);
	(*con)->exes = (t_exe **)malloc(sizeof(t_exe *));
	if ((*con)->exes == NULL)
		memerr_exit(1);
	(*con)->hasprinted = 0;
	(*con)->numpid = 0;
}
