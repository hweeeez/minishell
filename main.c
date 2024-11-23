/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hui-lim <hui-lim@student.42singapore.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:45:38 by hui-lim           #+#    #+#             */
/*   Updated: 2024/11/23 18:47:54 by hui-lim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell.h"

	//cc -lreadline main.c
void handle_signal(int sig)
{
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
