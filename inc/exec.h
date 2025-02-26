/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 21:10:21 by hui-lim           #+#    #+#             */
/*   Updated: 2025/01/14 21:10:25 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "minishell.h"

typedef struct s_sigs
{
	struct sigaction	ignore;
	struct sigaction	quit;
	struct sigaction	sigint;
	struct sigaction	sigpipe;
}				t_sigs;

typedef struct s_exe
{
	pid_t	pid;
	pid_t	childpid;
	int		pipefd[2];
	int		puts[2];
}				t_exe;

typedef struct s_execontainer
{
	pid_t	*pids;
	int		numpid;
	int		hasprinted;
	int		redir_status;
	int		skipnl;
	t_exe	**exes;
	t_sigs	**sigs;
	int		isbuiltin;
}				t_execontainer;

void	ft_coredump_msg(int status, t_shell **shell, t_execontainer **con);
void	init_exesigs(t_sigs **sigs);
void	do_sigaction(int sig1, int sig2, t_sigs *sigs);
int		execute(t_node *node, t_shell **shell);
int		exe_commands(t_node *node, t_execontainer **exe, t_shell **shell);
int		wait_children(t_execontainer **con, t_shell **shell);
void	closeputs(t_exe **exe);
void	initexenode(t_exe **exe);
void	executechild(t_node *node, t_execontainer **con, t_shell **shell);
void	exe_rightnode(t_execontainer **con, t_node *right, t_shell **shell);
int		get_redir(t_redir *redir, t_exe **exe, \
		t_shell **shell, t_execontainer **con);
int		has_redir(t_execontainer **exe, t_node *node, t_shell **shell);
int		ft_heredoc(t_redir *redirs, t_shell **shell);
int		ft_heredoc_exe(t_redir *redirs, t_shell **shell, int expand_flag);
int		checkif_builtin(t_shell **shell, char **cmd, t_execontainer **exe);
int		do_execution(t_shell **shell, char **cmd, t_execontainer **exe);
void	addchild(t_exe **add, t_execontainer **cont);
void	addpid(pid_t pid, t_execontainer **con);
void	addsig(t_sigs **add, t_execontainer **cont);
void	free_exe(t_execontainer **exe);

// void	exe_out(t_exe **exe, t_node *node);
// int		checkinput(int *input, t_node **node);

#endif
