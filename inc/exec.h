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
}				t_sigs;

typedef struct s_exe
{
	pid_t	pid;
	pid_t	childpid;
	int		pipefd[2];
	int		puts[2];
}				t_exe;

void	ft_coredump_msg(int status, int *exit_status, t_shell **shell);
void	init_exesigs(t_sigs **sigs);
void	do_sigaction(int sig1, int sig2, t_sigs *sigs);
int		execute(t_node *node, t_shell **shell);
int		exe_commands(t_node *node, t_exe **exe, t_shell **shell);
int		wait_children(t_shell **shell);
void	closeputs(t_exe **exe);
void	initexenode(t_exe **exe);
void	executechild(t_node *node, t_exe **exe, t_shell **shell);
void	exe_rightnode(t_exe **exe, t_node *right, t_shell **shell);
void	exe_out(t_exe **exe, t_node *node);
int		checkinput(int *input, t_node **node);
void	get_redir(t_redir *redir, t_exe **exe, t_shell **shell);
void	has_redir(t_exe **exe, t_node *node, t_shell **shell);
int		ft_heredoc(t_node *node, t_shell **shell);
int		checkif_builtin(t_shell **shell, char **cmd);
int		do_execution(t_shell **shell, char **cmd);
void	addchild(pid_t pid, t_shell **shell);

#endif
