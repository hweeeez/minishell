/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:56:44 by myuen             #+#    #+#             */
/*   Updated: 2024/11/04 21:00:08 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static int	wait_children(pid_t pid1, pid_t pid2)
{
	int	status;
	int	exit_status;

	exit_status = EXIT_NORMAL;
	waitpid(pid1, &status, 0);
	waitpid(pid2, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		exit_status = WTERMSIG(status) + FATAL_ERR_SIG;
	else
		exit_status = EXIT_FAILURE;
	return (exit_status);
}

static int	execute_pipeline(t_pipe *pipex)
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		ft_perror_exit(pipex, ERR_FORK);
	if (pipex->pid1 == 0)
		ft_execute_cmd1(pipex);
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		ft_perror_exit(pipex, ERR_FORK);
	if (pipex->pid2 == 0)
		ft_execute_cmd2(pipex);
	ft_close_pipes(pipex);
	return (wait_children(pipex->pid1, pipex->pid2));
}

int	pipex(char **argv, char **envp)
{
	t_pipe	pipex;
	int		exit_status;

	ft_memset(&pipex, 0, sizeof(pipex));
	exit_status = EXIT_NORMAL;
	if (ft_init_pipes(&pipex, argv, envp) != 0)
		return (ft_free_memory(&pipex), EXIT_FAILURE);
	exit_status = execute_pipeline(&pipex);
	ft_free_memory(&pipex);
	return (exit_status);
}
