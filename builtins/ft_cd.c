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

int	ft_cd(t_shell *shell, char *path)
{
	char	*new_path;
	char	*old_pwd;

	ft_putstr_fd("--minishell cd--\n", STDOUT_FILENO);
	new_path = get_new_cd_path(shell, path);
	if (!new_path && path && ft_strcmp(path, ".") != 0)
		return (1);
	if (ft_strcmp(path, ".") == 0)
		return (0);
	old_pwd = getcwd(NULL, 0);
	if (!old_pwd)
		return (1);
	if (chdir(new_path) != 0)
		return (handle_cd_error(old_pwd, path));
	return (update_pwd_vars(shell, old_pwd));
}
