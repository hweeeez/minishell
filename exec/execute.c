/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:11:22 by hui-lim           #+#    #+#             */
/*   Updated: 2025/02/03 15:54:02 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int has_redir(t_execontainer **con, t_node *node, t_shell **shell)
{
	int valid;
	t_exe *exe;

	exe = (*con)->exes[(*con)->numpid - 1];
	valid = 0;
	if (node->left->rootredir != NULL)
	{
		valid = get_redir(node->left->rootredir, &exe, shell, con);
		(*con)->redir_status = valid;
		return (valid);
	}
	(*con)->redir_status = -1;
	return (0);
}

int execute(t_node *node, t_shell **shell)
{
	t_node *left;
	t_execontainer *cont;
	t_exe *exe;

	cont = (t_execontainer *)malloc(sizeof(t_execontainer)); //this is not freed in some path
	if (!cont)
	{
		(void) cont; //handle error
	}
	ft_memset(cont, 0, sizeof(t_execontainer));
	cont->exes = NULL;
	left = node->left;
	if (left == NULL)
		return (0);
	if (node->type == NODE_PIPE)
	{
		//ft_memset(cont, 0, sizeof(t_execontainer));
		cont->exes = (t_exe **)malloc(sizeof(t_exe *)); //this is not freed in some path
		if (!cont->exes)
		{
			(void) cont->exes; //handle error
		}
		if (left->args != NULL && isbuiltin(left->args[0]) == 1)
		{
			(cont)->skipnl = 1;
			if (node->right == NULL)
			{
				if (node->left->rootredir != NULL)
				{
					initexenode(&(exe));
					addchild(&exe, &cont);
					exe_commands(node, &cont, shell);
					wait_children(&cont, shell);
				}
				else
					(*shell)->exit_status = checkif_builtin(shell, left->args, &cont);	
				return (free_exe(&cont), 0);
			}
		}
		initexenode(&exe);
		addchild(&exe, &cont);
		exe_commands(node, &cont, shell);
		wait_children(&cont, shell);
		if (cont->redir_status == 1)
			(*shell)->exit_status = cont->redir_status;
	}
	free_exe(&cont);
	return (0);
}

int exe_commands(t_node *node, t_execontainer **con, t_shell **shell)
{
	t_sigs *sigs;
	int canrun;
	pid_t pid;

	init_exesigs(&sigs);
	addsig(&sigs, con);
	pid = -1;
	canrun = has_redir(con, node, shell);
	if (node->right != NULL || (node->left->redirs != NULL && canrun == 0))
	{
		if (pipe((*con)->exes[(*con)->numpid - 1]->pipefd) == -1)
			return (-1);
	}
	if (canrun == 0)
		pid = fork();
	else if (node->right != NULL)
		pid = 1;
	addpid(pid, con);
	if (pid == 0) 
	{
		(*shell)->parent = 0;//need to change the (isparent?) flag in shell
		do_sigaction(SIGQUIT, SIGINT, (*con)->sigs[(*con)->numpid - 1]);
		executechild(node, con, shell);
	}
	else if (pid == -1)
		return (-1);
	else if (pid > 0)
	{
		sigaction(SIGINT, &((*con)->sigs[(*con)->numpid - 1]->ignore), NULL);
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
	}
	return (1);
}

void executechild(t_node *node, t_execontainer **con, t_shell **shell)
{
	t_exe *exe;

	exe = (*con)->exes[(*con)->numpid - 1];
	if ((exe)->puts[0] != STDIN_FILENO)
	{
		dup2((exe)->puts[0], STDIN_FILENO);
		close((exe)->puts[0]);
		if (node->right == NULL)
		{
			if ((exe)->pipefd[0] > -1)
				close((exe)->pipefd[0]);
			if ((exe)->pipefd[1] > -1)
				close((exe)->pipefd[1]);
		}
	}
	if ((exe)->puts[1] != STDOUT_FILENO)
	{
		dup2((exe)->puts[1], STDOUT_FILENO);
		close((exe)->puts[1]);
		if (node->right == NULL)
		{
			if ((exe)->pipefd[0] > -1)
				close((exe)->pipefd[0]);
			if ((exe)->pipefd[1] > -1)
				close((exe)->pipefd[1]);
		}
	}
	else if (node->right != NULL)
	{
		close((exe)->pipefd[0]);
		dup2(exe->pipefd[1], STDOUT_FILENO);
		close(exe->pipefd[1]);
	}
	do_execution(shell, node->left->args, con);
}
