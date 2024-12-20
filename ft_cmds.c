/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:56:17 by myuen             #+#    #+#             */
/*   Updated: 2024/11/04 20:55:47 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_execute_cmd1(t_pipe *pipex)
{
	if (!pipex->cmd1_path)
		ft_perror_exit(pipex, NULL);
	if (pipex->infile < 0 || pipex->pipe_fd[1] < 0)
		ft_perror_exit(pipex, NULL);
	dup2(pipex->infile, STDIN_FILENO);
	dup2(pipex->pipe_fd[1], STDOUT_FILENO);
	ft_close_pipes(pipex);
	execve(pipex->cmd1_path, pipex->cmd1_args, pipex->env);
	ft_perror_exit(pipex, ERR_CHILD);
}

void	ft_execute_cmd2(t_pipe *pipex)
{
	if (!pipex->cmd2_path)
		ft_perror_exit(pipex, NULL);
	if (pipex->outfile < 0 || pipex->pipe_fd[0] < 0)
		ft_perror_exit(pipex, NULL);
	dup2(pipex->pipe_fd[0], STDIN_FILENO);
	dup2(pipex->outfile, STDOUT_FILENO);
	ft_close_pipes(pipex);
	execve(pipex->cmd2_path, pipex->cmd2_args, pipex->env);
	ft_perror_exit(pipex, ERR_CHILD);
}
