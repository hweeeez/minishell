/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:16:32 by hui-lim           #+#    #+#             */
/*   Updated: 2025/01/30 16:16:34 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_received_sigint = 0;

void	exit_hd(int sig)
{
	(void) sig;
	g_received_sigint = 1;
	rl_replace_line("", 0);
	write (1, "\n", 1);
	rl_on_new_line();
	rl_replace_line(PROMPT, 0);
	rl_done = 1;
	return ;
}

static int	parsehd(char *s, char *file, int filefd)
{
	if (ft_strcmp(s, file) == 1 || g_received_sigint == 1)
	{
		free(s);
		close(filefd);
		return (1);
	}
	write(filefd, s, ft_strlen(s));
	write(filefd, "\n", 1);
	return (0);
}

static int	readhd(t_redir *redirs, int filefd)
{
	char	*s;

	while (g_received_sigint == 0)
	{
		s = readline("> ");
		if (s != NULL)
		{
			if (parsehd(s, redirs->file, filefd) == 1)
				break ;
		}
		else
		{
			printf("warning: here-document delimited by end-of-file\n");
			close(filefd);
			break ;
		}
		free(s);
	}
	if (g_received_sigint == 1)
	{
		close(filefd);
		unlink(HEREDOC_FILE);
		return (1);
	}
	return (0);
}

int	event(void)
{
	return (0);
}

int	ft_heredoc(t_node *node, t_shell **shell)
{
	int					filefd;
	t_redir				*redirs;
	struct sigaction	sig_int;
	t_exe				*exe;

	rl_event_hook = event;
	sig_int.sa_handler = exit_hd;
	g_received_sigint = 0;
	sigaction(SIGINT, &sig_int, NULL);
	redirs = node->left->rootredir;
	filefd = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (readhd(redirs, filefd) == 1)
		return (1);
	filefd = open(HEREDOC_FILE, O_RDONLY, 0644);
	node->left->redirs = redirs->next;
	initexenode(&exe);
	exe->puts[0] = filefd;
	exe_commands(node, &exe, shell);
	close (filefd);
	unlink(HEREDOC_FILE);
	free(exe);
	return (1);
}
