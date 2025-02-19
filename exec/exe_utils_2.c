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

void	ft_coredump_msg(int status, t_shell **shell)
{
	if (WIFSIGNALED(status))
	{
		if (WCOREDUMP(status))
		{
			if ((*shell)->hasprinted == 0)
				{
					write(1, "Quit (core dumped)", 18);
					write (1, "\n", 1);
					(*shell)->hasprinted = 1;
				}
			(*shell)->exit_status = ENOTRECOVERABLE;
		}
	}
}

static void	wait_pid(pid_t proc, t_shell **shell)
{
	int	status;
	//int	exit_status;
	pid_t	pid;

	status = 0;
	//exit_status = EXIT_NORMAL;
	while(1)
	{
		pid = waitpid(proc, &status, 0);
		if (pid == -1)
		{
			if (errno == ECHILD)
				break;
			if (errno == EINTR)
				continue;
			perror("waitpid");
			break;
		}
		if (pid > 0)
		{
			if (WIFEXITED(status))
				(*shell)->exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
			{
				(*shell)->exit_status = WTERMSIG(status) + FATAL_ERR_SIG;
			}
			else
				(*shell)->exit_status = EXIT_FAILURE;
			ft_coredump_msg(status, shell);
			break;
		}
	}
	//(*shell)->exit_status = exit_status;
}

int	wait_children(t_shell **shell)
{
	int	i;

	i = 0;
	while ((*shell)->numpid > 0)
	{
		wait_pid((*shell)->pids[i], shell);
		i++;
		(*shell)->numpid--;
	}
	return (0);
}

// static void	appendpid(pid_t pid, pid_t **arr, t_shell *shell)
// {
// 	pid_t		*temp;
// 	int		i;

// 	i = 0;
// 	temp = (int *)malloc(sizeof(pid_t) * (shell->numpid));
// 	if (*arr != NULL)
// 	{
// 		while (i < shell->numpid - 1)
// 		{
// 			temp[i] = (*arr)[i];
// 			i++;
// 		}
// 		free(*arr);
// 	}
// 	temp[i] = (pid);
// 	*arr = temp;
// }

void	addchild(pid_t pid, t_shell **shell)
{
	pid_t		*temp;
	int		i;

	(*shell)->numpid++;
	i = 0;
	temp = (int *)malloc(sizeof(pid_t) * ((*shell)->numpid));
	if ((*shell)->pids != NULL)
	{
		while (i < (*shell)->numpid - 1)
		{
			temp[i] = ((*shell)->pids)[i];
			i++;
		}
		free((*shell)->pids);
	}
	temp[i] = (pid);
	(*shell)->pids = temp;
}
