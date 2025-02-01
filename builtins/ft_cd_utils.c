/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:56:24 by myuen             #+#    #+#             */
/*   Updated: 2025/02/01 20:12:58 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_cd_home(t_shell *shell, char **new_path)
{
	*new_path = get_env_value(shell, "HOME");
	if (!*new_path)
	{
		ft_putstr_fd("cd: HOME not set\n", 2);
		return (1);
	}
	return (0);
}

static int	handle_cd_prev(t_shell *shell, char **new_path)
{
	*new_path = get_env_value(shell, "OLDPWD");
	if (!*new_path)
	{
		ft_putstr_fd("cd: OLDPWD not set\n", 2);
		return (1);
	}
	ft_putendl_fd(*new_path, 1);
	return (0);
}

char	*get_new_cd_path(t_shell *shell, char *path)
{
	if (!path)
	{
		if (handle_cd_home(shell, &path))
			return (NULL);
	}
	else if (ft_strcmp(path, "-") == 0)
	{
		if (handle_cd_prev(shell, &path))
			return (NULL);
	}
	else if (ft_strcmp(path, ".") == 0)
		return (NULL);
	return (path);
}
