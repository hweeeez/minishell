
#include "minishell.h"

//builtins need to write to stdout, but do not read from stdin (but we should still dup2)
int	do_execution(t_shell **shell, char **cmd)
{
	int	builtinvalue;

	builtinvalue = checkif_builtin(shell, cmd);
	if (builtinvalue == -1)
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

int	checkif_builtin(t_shell **shell, char **cmd)
{
	if (ft_strcmp(cmd[0], "echo") == 1)
		return (ft_echo(cmd));
	if (ft_strcmp(cmd[0], "cd") == 1)
		return (ft_cd(*shell, cmd[1]));
	if (ft_strcmp(cmd[0], "pwd") == 1)
		return (ft_pwd());
	if (ft_strcmp(cmd[0], "export") == 1)
		return (ft_export(*shell, cmd));
	if (ft_strcmp(cmd[0], "unset") == 1)
		return (ft_unset(*shell, cmd));
	if (ft_strcmp(cmd[0], "env") == 1)
		return (ft_env(*shell));
	if (ft_strcmp(cmd[0], "exit") == 1)
		return (ft_exit(*shell, cmd));
	return (-1);
}