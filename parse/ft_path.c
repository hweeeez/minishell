/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 14:57:34 by myuen             #+#    #+#             */
/*   Updated: 2025/02/02 17:49:42 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_path_in_env(char **envp)
{
	int		i;
	int		path_line_len;
	char	*path_value;

	i = 0;
	path_line_len = ft_strlen(PATH_LINE);
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], PATH_LINE, path_line_len) == 0)
		{
			path_value = ft_strdup(envp[i] + path_line_len);
			if (!path_value)
				return (NULL);
			return (path_value);
		}
		i++;
	}
	return (NULL);
}

static char	*try_path_with_cmd(char *dir, char *cmd)
{
	char	*temp;
	char	*full_path;

	temp = ft_strjoin(dir, "/");
	if (!temp)
		return (NULL);
	full_path = ft_strjoin(temp, cmd);
	free(temp);
	if (!full_path)
		return (NULL);
	if (access(full_path, F_OK) == 0)
	{
		if (access(full_path, X_OK) == 0)
			return (full_path);
		free(full_path);
		perror(cmd);
		return (NULL);
	}
	free(full_path);
	return (NULL);
}

static char	*check_path_directories(char **paths, char *cmd)
{
	char	*cmd_path;
	//char	**args;
	int		i;

	// args = ft_split(cmd, ' ');
	// if (!args)
	// {
	// 	ft_free_split(&paths);
	// 	return (NULL);
	// }
	i = 0;
	while (paths[i])
	{
		cmd_path = try_path_with_cmd(paths[i], cmd);
		if (cmd_path)
		{
			ft_free_split(&paths);
			// ft_free_split(&args);
			return (cmd_path);
		}
		i++;
	}
	ft_free_split(&paths);
	// ft_free_split(&args);
	return (NULL);
}

char	*ft_find_cmd_path(char *cmd, char ***cmd_args, char **envp)
{
	char	*env_path;
	char	**paths;

	if (!cmd || !*cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
		return (ft_check_direct_path(cmd, cmd_args));
	if (!envp)
		return (NULL);
	env_path = find_path_in_env(envp);
	if (!env_path)
		return (NULL);
	paths = ft_split(env_path, ':');
	free(env_path);
	if (!paths)
		return (NULL);
	return (check_path_directories(paths, cmd));
}
