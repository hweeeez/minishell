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
	int		has_hd;
	int		exe_hd;
}				t_exe;

void	ft_coredump_msg(int status);
void	init_exesigs(t_sigs **sigs);
void	do_sigaction(int sig1, int sig2, t_sigs *sigs);
int		execute(t_node *node, char **envp);
int		exe_commands(t_node *node, t_exe **exe, char **envp);
int		wait_children(t_exe **exe);
void	closeputs(t_exe **exe);
void	initexenode(t_exe **exe);
void	executechild(t_node *node, t_exe **exe, char **envp);
void	exe_rightnode(t_exe **exe, t_node *right, char **envp);
void	exe_out(t_exe **exe, t_node *node);
int		checkinput(int *input, t_node **node);
void	get_redir(t_redir *redir, t_exe **exe);
void	has_redir(t_exe **exe, t_node *node);
int		execute(t_node *node, char **envp);
int		ft_heredoc(t_node *node, char **envp);

#endif
