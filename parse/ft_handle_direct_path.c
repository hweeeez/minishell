/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_direct_path.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 20:31:47 by myuen             #+#    #+#             */
/*   Updated: 2025/02/02 18:47:57 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*try_full_path(char *cmd)
// {
// 	if (access(cmd, F_OK) == 0)
// 	{
// 		if (access(cmd, X_OK) == 0)
// 		{
// 			return (ft_strdup(cmd));
// 		}
// 		perror(cmd);
// 	}
// 	return (NULL);
// }

static char	*set_arg_with_full_path(char ***cmd_args, char *path)
{
	char	**new_args;

	new_args = (char **)malloc(sizeof(char *) * 2);
	if (!new_args)
		return (NULL);
	new_args[0] = ft_strdup(path);
	new_args[1] = NULL;
	if (*cmd_args)
		ft_free_split(cmd_args);
	*cmd_args = new_args;
	return (path);
}

char	*ft_check_direct_path(char *cmd, char ***cmd_args)
{
	char	*path;

	path = NULL;
	if (cmd && cmd_args)
	{
		if (check_path_type((const char *) cmd) == 3)
			return (set_arg_with_full_path(cmd_args, cmd));
		if ((*cmd_args != NULL))
		{
			if (is_executable((*cmd_args)[0]))
			{
				path = ft_strdup((*cmd_args)[0]);
				return (path);
			}
			else
				perror((*cmd_args)[0]);
		}	
	}
	return (NULL);
}
