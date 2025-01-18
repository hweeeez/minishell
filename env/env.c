/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:46:28 by myuen             #+#    #+#             */
/*   Updated: 2025/01/18 18:07:02 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env(char **env)
{
	size_t	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
}

static char	**dup_env(char **env)
{
	char	**new_env;
	size_t	i;
	size_t	size;

	size = 0;
	while (env[size])
		size++;
	new_env = (char **)malloc(sizeof(char *) * (size + 1));
	if (!new_env)
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env[i])
		{
			free_env(new_env);
			return (NULL);
		}
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = dup_env(env);
	if (!shell->env)
	{
		free(shell);
		return (NULL);
	}
	shell->exit_status = 0;
	shell->interactive = isatty(STDIN_FILENO);
	return (shell);
}

void	cleanup_shell(t_shell **shell)
{
	if (!(*shell))
		return ;
	if ((*shell)->env)
		free_env((*shell)->env);
	free(*shell);
	*shell = NULL;
}
