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
#include "tokenizer.h"

	//cc -lreadline main.c libft.c llist_utils.c string_utils.c token_utils.c tokenizer.c
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
	t_token *tokens;
    t_token *current;
    
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
			tokens = tokenize(s);
			if (!tokens)
			{
				printf("Error: Failed to tokenize input\n");
				return (1);
			}
			current = tokens;
			while (current)
			{
				printf("%s:%u\n", current->value,current->type);
				int fd = access(current->value, R_OK & & X_OK);
				if (fd > -1)
					
				current = current->next;
			}
		}
		if (s == NULL)
		{	
			rl_clear_history();
			exit(0);
		}
		free(s);
	}
}
