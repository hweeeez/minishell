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

typedef struct s_exebox
{
	pid_t	*pids;
	int		numpid;
	int		hasprinted;
	int		redir_status;
	int		skipnl;
	t_exe	**exes;
	t_sigs	**sigs;
	int		isbuiltin;
}				t_exebox;

void	ft_coredump_msg(int status, t_shell **shell, t_exebox **con);
void	init_exesigs(t_sigs **sigs);
void	do_sigaction(int sig1, int sig2, t_sigs *sigs);
int		execute(t_node *node, t_shell **shell);
int		exe_commands(t_node *node, t_exebox **exe, t_shell **shell);
int		wait_children(t_exebox **con, t_shell **shell);
void	closeputs(t_exe **exe);
void	initexenode(t_exe **exe);
void	executechild(t_node *node, t_exebox **con, t_shell **shell);
void	exe_rightnode(t_exebox **con, t_node *right, t_shell **shell);
int		get_redir(t_redir *redir, t_exe **exe, \
		t_shell **shell, t_exebox **con);
int		has_redir(t_exebox **exe, t_node *node, t_shell **shell);
int		ft_heredoc(t_redir *redirs, t_shell **shell);
int		ft_heredoc_exe(t_redir *redirs, t_shell **shell);
int		checkif_builtin(t_shell **shell, char **cmd, t_exebox **exe);
int		do_execution(t_shell **shell, char **cmd, t_exebox **exe);
void	addchild(t_exe **add, t_exebox **cont);
void	addpid(pid_t pid, t_exebox **con);
void	addsig(t_sigs **add, t_exebox **cont);
void	free_exe(t_exebox **exe);
int		parsehd_expand(char *s, char *file, int filefd, t_shell **shell);
void	handle_sigint(int filefd, t_shell **shell);
void	handle_eof(int filefd);
int		handle_redirout(t_redir *re, t_exe **x, t_shell **shell);

#endif
