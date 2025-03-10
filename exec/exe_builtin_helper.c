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

static void	handle_sigpipe(int signo)
{
	(void)signo;
}

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

	signal(SIGPIPE, handle_sigpipe);
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
	if ((*exe)->redir_status == 0)
		close_pipefds((*exe)->exes[(*exe)->numpid - 1]);
	return (exitchild(shell, 0, exe), 1);
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
