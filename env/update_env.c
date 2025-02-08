/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:46:28 by myuen             #+#    #+#             */
/*   Updated: 2025/02/01 20:24:03 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_env_str(const char *key, const char *value)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, value);
	free(temp);
	return (result);
}

static int	update_existing_env(t_shell *shell, const char *key, \
const char *value, size_t key_len)
{
	int		i;
	char	*new_str;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], key, key_len) == 0 \
			&& shell->env[i][key_len] == '=')
		{
			new_str = create_env_str(key, value);
			if (!new_str)
				return (1);
			free(shell->env[i]);
			shell->env[i] = new_str;
			return (0);
		}
		i++;
	}
	return (2);
}

static int	copy_env_entries(char **new_env, char **old_env, char *new_str)
{
	int	size;

	size = 0;
	while (old_env[size])
	{
		new_env[size] = ft_strdup(old_env[size]);
		if (!new_env[size])
		{
			freestrl(new_env);
			free(new_str);
			return (-1);
		}
		size++;
	}
	return (size);
}

static int	add_new_env(t_shell *shell, const char *key, const char *value)
{
	char	**new_env;
	char	*new_str;
	int		size;

	new_str = create_env_str(key, value);
	if (!new_str)
		return (1);
	size = 0;
	while (shell->env[size])
		size++;
	new_env = (char **)malloc(sizeof(char *) * (size + 2));
	if (!new_env)
	{
		free(new_str);
		return (1);
	}
	size = copy_env_entries(new_env, shell->env, new_str);
	if (size == -1)
		return (1);
	new_env[size] = new_str;
	new_env[size + 1] = NULL;
	freestrl(shell->env);
	shell->env = new_env;
	return (0);
}

int	update_env(t_shell *shell, const char *key, const char *value)
{
	size_t	env_size;
	int		update_result;
	size_t	key_len;

	if (!key || !shell->env)
		return (1);
	key_len = ft_strlen(key);
	update_result = update_existing_env(shell, key, value, key_len);
	if (update_result != 2)
		return (update_result);
	env_size = 0;
	while (shell->env[env_size])
		env_size++;
	return (add_new_env(shell, key, value));
}
