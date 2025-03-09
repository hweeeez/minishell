/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:10:54 by hui-lim           #+#    #+#             */
/*   Updated: 2025/01/14 21:10:56 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_fd(t_exe *exe, int i)
{
	if ((exe)->puts[0] != STDIN_FILENO && \
		(exe)->puts[0] > -1 && (i == 0 || i == 1))
	{
		if (dup2((exe)->puts[0], STDIN_FILENO) == -1)
			perror("Error");
		close((exe)->puts[0]);
	}
	if ((exe)->puts[1] != STDOUT_FILENO && \
		(exe)->puts[1] > -1 && (i == 0 || i == 2))
	{
		if (dup2((exe)->puts[1], STDOUT_FILENO) == -1)
			perror("Error");
		close((exe)->puts[1]);
	}
}

void	restore_fd(t_exebox **b, int ogout, int ogin)
{
	t_exe	*exe;

	exe = (*b)->exes[(*b)->numpid - 1];
	if (exe->puts[0] != STDIN_FILENO)
	{
		if (dup2(ogin, STDIN_FILENO) == -1)
			perror("Error");
		close(ogin);
	}
	if (exe->puts[1] != STDOUT_FILENO)
	{
		if (dup2(ogout, STDOUT_FILENO) == -1)
			perror("Error");
		close(ogout);
	}
}

void	closeputs(t_exe **exe)
{
	if ((*exe)->puts[0] != STDIN_FILENO && (*exe)->puts[0] > -1)
		close((*exe)->puts[0]);
	if ((*exe)->puts[1] != STDOUT_FILENO && (*exe)->puts[1] > -1)
		close((*exe)->puts[1]);
}

void	exe_rightnode(t_exebox **con, t_node *right, t_shell **shell)
{
	t_exe	*childexe;
	t_exe	*exe;

	exe = (*con)->exes[(*con)->numpid - 1];
	if ((exe)->pipefd[1] > -1)
		close((exe)->pipefd[1]);
	initexenode(&childexe);
	childexe->puts[0] = (exe)->pipefd[0];
	addchild(&childexe, con);
	exe_commands(right, con, shell);
}

void	initexenode(t_exe **exe)
{
	(*exe) = (t_exe *)malloc(sizeof(t_exe));
	if (*(exe) == NULL)
		memerr_exit(1);
	(*exe)->childpid = -1;
	(*exe)->pid = -1;
	(*exe)->puts[0] = STDIN_FILENO;
	(*exe)->puts[1] = STDOUT_FILENO;
	(*exe)->pipefd[0] = -1;
	(*exe)->pipefd[1] = -1;
}
