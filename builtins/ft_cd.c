/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:56:24 by myuen             #+#    #+#             */
/*   Updated: 2025/02/02 21:02:47 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_cd_args(char **cmd)
{
	if (cmd[1 + 1] != NULL)
	{
		ft_putstr_fd("cd: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	return (0);
}

static int	handle_cd_error(char *old_pwd, char *path)
{
	free(old_pwd);
	ft_putstr_fd("cd: ", STDERR_FILENO);
	ft_putstr_fd(path, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	perror("");
	return (1);
}

static int	update_pwd_vars(t_shell *shell, char *old_pwd)
{
	char	*current_pwd;

	update_env(shell, "OLDPWD", old_pwd);
	free(old_pwd);
	current_pwd = getcwd(NULL, 0);
	if (!current_pwd)
		return (1);
	update_env(shell, "PWD", current_pwd);
	free(current_pwd);
	return (0);
}

int	ft_cd(t_shell *shell, char **cmd)
{
	char	*new_path;
	char	*old_pwd;

	//ft_putstr_fd("--minishell cd--\n", STDOUT_FILENO);
	if (check_cd_args(cmd))
	{
		return (1);
	}
	new_path = get_new_cd_path(shell, cmd[1]);
	if (!new_path && cmd[1] && ft_strcmp(cmd[1], ".") != 0)
		return (1);
	if (ft_strcmp(cmd[1], ".") == 0)
		return (0);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	if (chdir(new_path) != 0)
		return (handle_cd_error(old_pwd, cmd[1]));
	return (update_pwd_vars(shell, old_pwd));
}
