/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:21:01 by hui-lim           #+#    #+#             */
/*   Updated: 2025/01/29 17:21:03 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	quitchild(int sig)//, siginfo_t *info, void *ucontext)
{
	(void) sig;
	exit(0);
}

void	init_exesigs(t_sigs **sigs)
{
	(*sigs) = (t_sigs *)malloc(sizeof(t_sigs));
	if (!(*sigs))
	{
		(void) (*sigs); //handle error
	}
	ft_memset(&(*sigs)->sigpipe, 0, sizeof((*sigs)->sigpipe));
	(*sigs)->sigpipe.sa_handler = SIG_IGN;
	ft_memset(&(*sigs)->ignore, 0, sizeof((*sigs)->ignore));
	(*sigs)->ignore.sa_handler = SIG_IGN;
	//sigemptyset(&((*sigs)->ignore).sa_mask);
	//(*sigs)->ignore.sa_flags = 0;
	ft_memset(&(*sigs)->sigint, 0, sizeof((*sigs)->sigint));
	(*sigs)->sigint.sa_handler = quitchild;
	//sigemptyset(&((*sigs)->sigint).sa_mask);
	//(*sigs)->sigint.sa_flags = 0;
	ft_memset(&(*sigs)->quit, 0, sizeof((*sigs)->quit));
	(*sigs)->quit.sa_handler = NULL;
	//sigemptyset(&((*sigs)->quit).sa_mask);
	//(*sigs)->quit.sa_flags = 0;
}

void	do_sigaction(int sig1, int sig2, t_sigs *sigs)
{
	if (sigaction(SIGPIPE, &(sigs->sigpipe), NULL) == -1)
		return ;
	if (sig1 == SIGQUIT)
		sigaction(SIGQUIT, &(sigs->quit), NULL);
	if (sig2 == SIGINT)
		sigaction(SIGINT, &(sigs->sigint), NULL);
}
