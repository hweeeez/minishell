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

void	ft_coredump_msg(int status, t_shell **shell, t_execontainer **con)
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
			(*shell)->exit_status = ENOTRECOVERABLE;
		}
		if ((*con)->skipnl == 0)
			write (1, "\n", 1);
	}
}

static void	wait_pid(pid_t proc, t_shell **shell, t_execontainer **con)
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
			ft_coredump_msg(status, shell, con);
			break;
		}
	}
	//(*shell)->exit_status = exit_status;
}

int	wait_children(t_execontainer **con, t_shell **shell)
{
	int	i;
	int	j;

	i = 0;
	j = (*con)->numpid;
	while (j> 0)
	{
		wait_pid((*con)->pids[i], shell, con);
		i++;
		j--;
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

void	addpid(pid_t pid, t_execontainer **con)
{
	pid_t		*temp;
	int		i;

	//(*con)->numpid++;
	i = 0;
	temp = (int *)malloc(sizeof(pid_t) * ((*con)->numpid));
	if (!temp)
		memerr_exit(1);
	if ((*con)->pids != NULL)
	{
		while (i < (*con)->numpid - 1)
		{
			temp[i] = ((*con)->pids)[i];
			i++;
		}
		free((*con)->pids);
	}
	temp[i] = (pid);
	(*con)->pids = temp;
}

// void	addchild(void **add, void ***array, t_execontainer **cont, size_t size)
// {
// 	void	**temp;
// 	int		i;

// 	//(*cont)->numpid++;
// 	i = 0;
// 	temp = malloc(size * ((*cont)->numpid));
// 	if (array != NULL)
// 	{
// 		while (i < (*cont)->numpid - 1)
// 		{
// 			temp[i] = (*array)[i];
// 			ft_memcpy(temp + i, *array + i, size);
// 			i++;
// 		}
// 		free((*cont)->pids);
// 	}
// 	ft_memcpy(temp + i, *add, size);
// 	(*array) = temp;
// }

void	addchild(t_exe **add, t_execontainer **cont)
{
	t_exe	**temp;
	int		i;

	(*cont)->numpid++;
	i = 0;
	temp = (t_exe **)malloc(sizeof(t_exe) * ((*cont)->numpid));
	if (!temp)
		memerr_exit(1);
	if ((*cont)->exes != NULL)
	{
		while (i < (*cont)->numpid - 1)
		{
			temp[i] = ((*cont)->exes)[i];
			i++;
		}
		free((*cont)->exes);
	}
	temp[i] = *add;
	((*cont)->exes) = temp;
}

void	addsig(t_sigs **add, t_execontainer **cont)
{
	t_sigs	**temp;
	int		i;

	i = 0;
	temp = (t_sigs **)malloc(sizeof(t_sigs) * ((*cont)->numpid));
	if (!temp)
		memerr_exit(1);
	if ((*cont)->sigs != NULL)
	{
		while (i < (*cont)->numpid - 1)
		{
			temp[i] = ((*cont)->sigs)[i];
			i++;
		}
		free((*cont)->sigs);
	}
	temp[i] = *add;
	((*cont)->sigs) = temp;
}
