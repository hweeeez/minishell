/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:46:28 by myuen             #+#    #+#             */
/*   Updated: 2025/02/01 19:52:53 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_working_dir(void)
{
	char	*cwd;
	char	*dir;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("getcwd failed");
		return (NULL);
	}
	dir = ft_strdup(cwd);
	free(cwd);
	if (!dir)
		return (NULL);
	return (dir);
}

char	*get_env_value(t_shell *shell, const char *key)
{
	int		i;
	size_t	key_len;

	if (!key || !shell->env)
		return (NULL);
	key_len = ft_strlen(key);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, key_len) == 0 \
			&& shell->env[i][key_len] == '=')
			return (shell->env[i] + key_len + 1);
		i++;
	}
	return (NULL);
}

int	find_env(t_shell *shell, const char *key)
{
	int		i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, ft_strlen(key)) == 0)
		{
			return (1);
		}
		i++;
	}
	return (0);
}
