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

void	ft_coredump_msg(int status)
{
	if (WIFSIGNALED(status))
	{
		if (WCOREDUMP(status))
		{
			write(1, "Quit (core dumped)", 18);
		}
		write (1, "\n", 1);
	}
}

int	wait_children(t_exe **exe)
{
	int	status;
	int	exit_status;

	exit_status = EXIT_NORMAL;
	waitpid((*exe)->pid, &status, 0);
	if ((*exe)->childpid > -1)
		waitpid((*exe)->childpid, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_status = WTERMSIG((*exe)->childpid) + FATAL_ERR_SIG;
	else
		exit_status = EXIT_FAILURE;
	ft_coredump_msg(status);
	return (exit_status);
}
