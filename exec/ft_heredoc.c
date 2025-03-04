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

int	event(void)
{
	return (0);
}

int	parsehd(char *s, char *file, int filefd, t_shell **shell)
{
	char	*temp;

	if (ft_strcmp(s, file) == 1 || g_received_sigint == 1)
	{
		free(s);
		close(filefd);
		return (1);
	}
	if ((*shell)->expand_flag == 1)
	{
		temp = s;
		s = expand_heredoc((const char *)s, *shell);
		free (temp);
	}
	write(filefd, s, ft_strlen(s));
	write(filefd, "\n", 1);
	free(s);
	return (0);
}

int	readhd(t_redir *redirs, int filefd, t_shell **shell)
{
	char	*s;

	while (g_received_sigint == 0)
	{
		s = readline("> ");
		if (s != NULL)
		{
			if (parsehd(s, redirs->file, filefd, shell) == 1)
				break ;
		}
		else
		{
			handle_eof(filefd);
			break ;
		}
	}
	if (g_received_sigint == 1)
		return (handle_sigint(filefd, shell), 130);
	return (0);
}

int	ft_heredoc_exe(t_redir *redirs, t_shell **shell)
{
	int					filefd;
	struct sigaction	sig_int;

	rl_event_hook = event;
	g_received_sigint = 0;
	ft_memset(&sig_int, 0, sizeof(sig_int));
	sig_int.sa_handler = exit_hd;
	if (sigaction(SIGINT, &sig_int, NULL) == -1)
		return (-1);
	if (check_path_type(HEREDOC_FILE) == TYPE_FILE)
	{
		filefd = open(HEREDOC_FILE, O_RDONLY, 0644);
		unlink(HEREDOC_FILE);
		close(filefd);
	}
	filefd = open(HEREDOC_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (readhd(redirs, filefd, shell) == 130)
		return (130);
	close (filefd);
	return (filefd);
}
