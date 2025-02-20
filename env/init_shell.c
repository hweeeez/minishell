/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 18:46:28 by myuen             #+#    #+#             */
/*   Updated: 2025/02/01 19:48:55 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(char **env)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env = dup_split(env);
	if (!shell->env)
	{
		cleanup_shell(&shell);
		return (NULL);
	}
	shell->exit_status = 0;
	shell->interactive = isatty(STDIN_FILENO);
	shell->numpid = 0;
	shell->hasprinted = 0;
	shell->pids = NULL;
	shell->token = NULL;
	shell->root = NULL;
	shell->skipnl = 0;
	return (shell);
}

void	cleanup_shell(t_shell **shell)
{
	if (!shell || !(*shell))
		return ;
	if ((*shell)->token)
	{
		free_token_list(&(*shell)->token);
		(*shell)->token = NULL;
	}
	if ((*shell)->env)
	{
		free_split((*shell)->env);
		(*shell)->env = NULL;
	}
	if ((*shell)->root)
	{
		freetree(&((*shell)->root));
		(*shell)->root = NULL;
	}
	free(*shell);
	*shell = NULL;
}
