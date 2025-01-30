/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 21:04:21 by myuen             #+#    #+#             */
/*   Updated: 2025/01/07 19:18:21 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal(int sig)
{
	(void) sig;
	rl_replace_line("", 0);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	setup_signals(t_sigacts **sig)
{
	struct sigaction	quit;

	(*sig) = (t_sigacts *)malloc(sizeof(t_sigacts));
	ft_memset(&(*sig)->sa, 0, sizeof((*sig)->sa));
	ft_memset(&quit, 0, sizeof(quit));
	quit.sa_handler = SIG_IGN;
	(*sig)->sa.sa_handler = handle_signal;
	sigemptyset(&(*sig)->sa.sa_mask);
	(*sig)->sa.sa_flags = 0;
	if (sigaction(SIGQUIT, &quit, NULL) == -1)
		return (1);
	if (sigaction(SIGINT, &(*sig)->sa, NULL) == -1)
		return (1);
	return (0);
}
