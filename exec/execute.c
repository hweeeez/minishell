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

int	has_redir(t_exebox **con, t_node *node, t_shell **shell)
{
	int		valid;
	t_exe	*exe;

	exe = (*con)->exes[(*con)->numpid - 1];
	valid = 0;
	if (node->left->rootredir != NULL)
	{
		valid = get_redir(node->left->rootredir, &exe, shell, con);
		(*con)->redir_status = valid;
		if (valid)
			cleanup_redirs(*(*con)->exes);
		return (valid);
	}
	(*con)->redir_status = -1;
	return (0);
}

static void	init_exe(t_exe **exe, t_exebox **box, t_shell **shell, t_node *node)
{
	initexenode(exe);
	addchild(exe, box);
	exe_commands(node, box, shell);
	wait_children(box, shell);
}

static int	redir_builtin(t_exe **exe, t_shell **s, t_exebox **b, t_node *left)
{
	int		valid;
	int		og_stdout;
	int		og_stdin;

	initexenode(exe);
	addchild(exe, b);
	valid = get_redir(left->rootredir, exe, s, b);
	if (valid == 1)
		return (0);
	if (dup_og(&og_stdout, &og_stdin) == -1)
		return (ft_exit(s, NULL, b), -1);
	if (ft_strcmp(left->args[0], "exit") == 1)
		closeput((*exe)->puts[0], (*exe)->puts[1]);
	else
	{
		if ((*exe)->puts[0] != STDIN_FILENO && !left->args[0])
			write(1, "\n", 1);
		dup_fd(*exe, s, b, 0);
	}
	checkif_builtin(s, left->args, b);
	restore_fd(b, og_stdout, og_stdin, s);
	closeput((*exe)->puts[0], (*exe)->puts[1]);
	if (valid == 1)
		(*s)->exit_status = valid;
	return (close(og_stdout), close(og_stdin), 0);
}

static int	onlybuiltin(t_exebox **box, t_node *node, t_exe **exe, t_shell **s)
{
	t_node			*left;

	left = node->left;
	if (left->args != NULL && isbuiltin(left->args[0]) == 1)
	{
		if (node->right == NULL)
		{
			if (node->left->rootredir != NULL)
				redir_builtin(exe, s, box, left);
			else
				(*s)->exit_status = checkif_builtin(s, left->args, box);
			if (ft_strcmp(left->args[0], "echo") == 1 && \
				left->rootredir == NULL && left->args[1] == NULL)
				write(1, "\n", 1);
			return (free_exe(box), 1);
		}
	}
	return (0);
}

int	execute(t_node *node, t_shell **shell)
{
	t_node			*left;
	t_exebox		*box;
	t_exe			*exe;

	box = (t_exebox *)malloc(sizeof(t_exebox));
	if (!box)
		memerr_exit(1);
	ft_memset(box, 0, sizeof(t_exebox));
	box->exes = NULL;
	left = node->left;
	if (left == NULL)
		return (free(box), 0);
	if (node->type == NODE_PIPE)
	{
		box->exes = (t_exe **)malloc(sizeof(t_exe *));
		if (box->exes == NULL)
			memerr_exit(1);
		if (onlybuiltin(&box, node, &exe, shell) != 0)
			return (0);
		init_exe(&exe, &box, shell, node);
		if (box->redir_status == 1)
			(*shell)->exit_status = box->redir_status;
	}
	free_exe(&box);
	return (0);
}
