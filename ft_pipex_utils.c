/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:59:10 by myuen             #+#    #+#             */
/*   Updated: 2024/11/05 16:44:13 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_pipex.h"

void	ft_free_split(char ***split)
{
	int	i;

	i = 0;
	if (*split)
	{
		while ((*split)[i])
		{
			free((*split)[i]);
			(*split)[i] = NULL;
			i++;
		}
		free(*split);
		*split = NULL;
	}
}

void	ft_perror_exit(t_pipe *pipex, char *msg)
{
	if (msg)
		perror(msg);
	ft_close_pipes(pipex);
	ft_free_memory(pipex);
	exit(EXIT_FAILURE);
}

static void	close_one_fd(int *fd)
{
	if (*fd != -1)
	{
		close (*fd);
		*fd = -1;
	}	
}

void	ft_close_pipes(t_pipe *pipex)
{
	close_one_fd(&pipex->pipe_fd[0]);
	close_one_fd(&pipex->pipe_fd[1]);
	close_one_fd(&pipex->outfile);
	close_one_fd(&pipex->infile);
}

void	ft_free_memory(t_pipe *pipex)
{
	if (pipex->cmd1_path)
	{
		free(pipex->cmd1_path);
		pipex->cmd1_path = NULL;
	}
	if (pipex->cmd2_path)
	{
		free(pipex->cmd2_path);
		pipex->cmd2_path = NULL;
	}
	ft_free_split(&pipex->cmd1_args);
	ft_free_split(&pipex->cmd2_args);
}
