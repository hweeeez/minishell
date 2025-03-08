/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:27:22 by myuen             #+#    #+#             */
/*   Updated: 2025/02/19 19:27:30 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cleanup_redirs(t_exe *exe)
{
	if (exe->puts[0] != STDIN_FILENO && exe->puts[0] > 0)
	{
		close(exe->puts[0]);
		exe->puts[0] = STDIN_FILENO;
	}
	if (exe->puts[1] != STDOUT_FILENO && exe->puts[1] > 0)
	{
		close(exe->puts[1]);
		exe->puts[1] = STDOUT_FILENO;
	}
}

void	ft_coredump_msg(int status, t_shell **shell, t_exebox **con)
{
	if (WIFSIGNALED(status))
	{
		if (WCOREDUMP(status))
		{
			if ((*con)->hasprinted == 0)
			{
				write(1, "Quit (core dumped)", 18);
				(*con)->hasprinted = 1;
			}
		}
		(*shell)->exit_status = 128 + WTERMSIG(status);
		if ((*con)->skipnl == 0)
		{
			write (1, "\n", 1);
			(*con)->skipnl = 1;
		}
	}
}

static void	check_errno(t_shell **shell, int status)
{
	if (WIFEXITED(status))
		(*shell)->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		(*shell)->exit_status = WTERMSIG(status) + FATAL_ERR_SIG;
	else
		(*shell)->exit_status = EXIT_FAILURE;
}

static void	wait_pid(pid_t proc, t_shell **shell, t_exebox **con)
{
	int		status;
	pid_t	pid;

	status = 0;
	while (1)
	{
		pid = waitpid(proc, &status, 0);
		if (pid == -1)
		{
			if (errno == ECHILD)
				break ;
			if (errno == EINTR)
				continue ;
			break ;
		}
		if (pid > 0)
		{
			check_errno(shell, status);
			ft_coredump_msg(status, shell, con);
			break ;
		}
	}
}

int	wait_children(t_exebox **con, t_shell **shell)
{
	int	i;
	int	j;

	i = 0;
	j = (*con)->numpid;
	while (j > 0)
	{
		wait_pid((*con)->pids[i], shell, con);
		i++;
		j--;
	}
	return (0);
}
