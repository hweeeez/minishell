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
	g_received_sigint = 1;
}

int	setup_signals(struct sigaction *sig)
{
	struct sigaction	quit;

	ft_memset(sig, 0, sizeof(*sig));
	ft_memset(&quit, 0, sizeof(quit));
	quit.sa_handler = SIG_IGN;
	(*sig).sa_handler = handle_signal;
	if (sigaction(SIGQUIT, &quit, NULL) == -1)
		return (1);
	if (sigaction(SIGINT, sig, NULL) == -1)
		return (1);
	return (0);
}
