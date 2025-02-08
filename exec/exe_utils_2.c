#include "minishell.h"

void	ft_coredump_msg(int status, int *exit_status)
{
	if (WIFSIGNALED(status))
	{
		if (WCOREDUMP(status))
		{
			write(1, "Quit (core dumped)", 18);
			(*exit_status) = ENOTRECOVERABLE;
		}
		write (1, "\n", 1);
	}
}

// static void	wait_pid(pid_t pid)
// {
// 	int	status;
// 	int	exit_status;

// 	status = 0;
// 	exit_status = EXIT_NORMAL;
// 	waitpid(pid, &status, 0);
// 	if (WIFEXITED(status))
// 		exit_status = WEXITSTATUS(status);
// 	else if (WIFSIGNALED(status))
// 		exit_status = WTERMSIG(pid) + FATAL_ERR_SIG;
// 	else
// 		exit_status = EXIT_FAILURE;
// 	ft_coredump_msg(status, &exit_status);
// 	//(*shell)->exit_status = exit_status;
// 	return (exit_status);
// }

int	wait_children(t_exe **exe, t_shell **shell)
{
	int	status;
	int	exit_status;
	pid_t	pid;

	status = 0;
	exit_status = EXIT_NORMAL;
	while(1)
	{
		pid = waitpid((*exe)->pid, &status, 0);
		if (pid == -1)
		{
			if (errno == ECHILD)
				break;
		}
		if (pid > 0)
		{
			if (WIFEXITED(status))
				exit_status = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_status = WTERMSIG(status) + FATAL_ERR_SIG;
			else
				exit_status = EXIT_FAILURE;
			break;
		}
		ft_coredump_msg(status, &exit_status);
	}
	(*shell)->exit_status = exit_status;
	return (exit_status);
}

static void	appendpid(pid_t pid, pid_t **arr, t_shell *shell)
{
	pid_t		*temp;
	int		i;

	i = 0;
	temp = (int *)malloc(sizeof(pid_t) * (shell->numpid));
	if (arr != NULL)
	{
		while (i < shell->numpid)
		{
			temp[i] = (*arr)[i];
			i++;
		}
		free(arr);
	}
	temp[i] = (pid);
	*arr = temp;
}

void	addchild(pid_t pid, t_shell **shell)
{
	(*shell)->numpid++;
	appendpid(pid, &(*shell)->pids, *shell);
}
