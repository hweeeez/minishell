
#include "minishell.h"

//builtins need to write to stdout, but do not read from stdin (but we should still dup2)
int	do_execution(t_shell **shell, char **cmd)
{
	if (checkif_builtin(shell, cmd) == -1)
	{
		if (execve(cmd[0], cmd, (*shell)->env) == -1)
		{
			perror(cmd[0]);
			exit(0);
		}
	}
	else
		exit(0);
	return (1);
}