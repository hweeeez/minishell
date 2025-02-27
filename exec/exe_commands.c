/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 21:08:59 by hui-lim           #+#    #+#             */
/*   Updated: 2025/02/27 21:12:29 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_exe_sigs(int *pid, t_sigs **sigs, t_exebox **con)
{
	init_exesigs(sigs);
	addsig(sigs, con);
	*pid = -1;
}

static int	handle_parent(t_node *node, t_exebox **con, t_shell **shell)
{
	t_sigs	*sig;

	sig = (*con)->sigs[(*con)->numpid - 1];
	if (sigaction(SIGINT, &(sig->ignore), NULL) == -1)
		return (-1);
	if (node->right == NULL)
	{
		if ((*con)->exes[(*con)->numpid - 1]->pipefd[0] > -1)
			close((*con)->exes[(*con)->numpid - 1]->pipefd[0]);
		if ((*con)->exes[(*con)->numpid - 1]->pipefd[1] > -1)
			close((*con)->exes[(*con)->numpid - 1]->pipefd[1]);
	}
	closeputs(&(*con)->exes[(*con)->numpid - 1]);
	if (node->right != NULL)
		exe_rightnode(con, node->right, shell);
	return (1);
}

static void	handle_child(t_node *node, t_exebox **con, t_shell **shell)
{
	(*shell)->parent = 0;
	do_sigaction(SIGQUIT, SIGINT, (*con)->sigs[(*con)->numpid - 1]);
	executechild(node, con, shell);
}

static void	init_exe_commands(t_node *node, t_exebox **c, t_shell **s, int *ok)
{
	*ok = has_redir(c, node, s);
	if (node->right != NULL || (node->left->redirs != NULL && *ok == 0))
	{
		if (pipe((*c)->exes[(*c)->numpid - 1]->pipefd) == -1)
			ft_exit(s, NULL, c);
	}
}

int	exe_commands(t_node *node, t_exebox **con, t_shell **shell)
{
	t_sigs	*sigs;
	int		canrun;
	pid_t	pid;

	init_exe_sigs(&pid, &sigs, con);
	init_exe_commands(node, con, shell, &canrun);
	if (canrun == 0)
		pid = fork();
	else if (node->right != NULL)
		pid = 1;
	addpid(pid, con);
	if (pid == 0)
		handle_child(node, con, shell);
	else if (pid == -1)
		return (ft_exit(shell, NULL, con), -1);
	else if (pid > 0)
		handle_parent(node, con, shell);
	return (1);
}
