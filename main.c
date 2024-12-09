/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: myuen <myuen@student.42singapore.sg>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:45:38 by hui-lim           #+#    #+#             */
/*   Updated: 2024/12/09 21:28:37 by myuen            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

	//cc -lreadline main.c
void handle_signal(int sig)
{
	(void) sig; //can't have unused variable
	rl_replace_line("", 0);
	write (1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

int	main()
{
	char	*s;
	struct	sigaction sa;
	struct	sigaction quit;

	quit.sa_handler = SIG_IGN;
	sa.sa_handler = handle_signal;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &quit, NULL);
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (0);
	while (1)
	{
		s = readline(PROMPT);
		if (s != NULL)
		{
			add_history(s);
		}
		if (s == NULL)
		{	
			rl_clear_history();
			exit(0);
		}
		free(s);
	}
}
