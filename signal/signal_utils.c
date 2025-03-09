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

static void	quitchild(int sig)
{
	(void) sig;
	exit(0);
}

void	init_exesigs(t_sigs **sigs)
{
	(*sigs) = (t_sigs *)malloc(sizeof(t_sigs));
	if (!(*sigs))
		memerr_exit(1);
	ft_memset(&(*sigs)->ignore, 0, sizeof((*sigs)->ignore));
	(*sigs)->ignore.sa_handler = SIG_IGN;
	ft_memset(&(*sigs)->sigint, 0, sizeof((*sigs)->sigint));
	(*sigs)->sigint.sa_handler = quitchild;
	ft_memset(&(*sigs)->quit, 0, sizeof((*sigs)->quit));
	(*sigs)->quit.sa_handler = NULL;
}

void	do_sigaction(int sig1, int sig2, t_sigs *sigs)
{
	if (sig1 == SIGQUIT)
	{
		if (sigaction(SIGQUIT, &(sigs->quit), NULL) == -1)
			perror("Error");
	}
	if (sig2 == SIGINT)
	{
		if (sigaction(SIGINT, &(sigs->sigint), NULL) == -1)
			perror("Error");
	}
}
