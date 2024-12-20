/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:56:08 by myuen             #+#    #+#             */
/*   Updated: 2024/11/04 22:20:15 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

static void	open_files(t_pipe *pipex, char **argv)
{
	pipex->infile = open(argv[1], O_RDONLY);
	if (pipex->infile < 0)
		perror(argv[1]);
	pipex->outfile = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC,
			FILE_PERMISSION);
	if (pipex->outfile < 0)
		perror(argv[4]);
}

static int	open_pipe(t_pipe *pipex)
{
	if (pipe(pipex->pipe_fd) < 0)
	{
		perror(ERR_PIPE);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	ft_init_pipes(t_pipe *pipex, char **argv, char **envp)
{
	pipex->env = envp;
	pipex->pid1 = -1;
	pipex->pid2 = -1;
	open_files(pipex, argv);
	if (open_pipe(pipex) != 0)
		return (EXIT_FAILURE);
	pipex->cmd1_args = ft_split(argv[2], ' ');
	pipex->cmd2_args = ft_split(argv[3], ' ');
	pipex->cmd1_path = ft_find_cmd_path(argv[2], &pipex->cmd1_args, envp);
	if (!pipex->cmd1_path)
		ft_fprintf(STDERR_FILENO, "%s: not valid\n", argv[2]);
	pipex->cmd2_path = ft_find_cmd_path(argv[3], &pipex->cmd2_args, envp);
	if (!pipex->cmd2_path)
		ft_fprintf(STDERR_FILENO, "%s: not valid\n", argv[3]);
	return (EXIT_SUCCESS);
}
