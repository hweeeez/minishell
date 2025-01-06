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
	//cc -g -lreadline main.c libft.c llist_utils.c string_utils.c token_utils.c tokenizer.c createtree.c ft_handle_direct_path.c ft_path.c treehelper.c traversetree.c ft_heredoc.c -lm
void handle_signal(int sig)
{
	rl_replace_line("", 0);
	write (1, "\n", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	get_pwd()
{
	char*	dir;
	size_t size;
	char *buf;

	dir = getcwd(buf, size);
	printf("%s", dir);
}

int	main(int argc, char** argv, char** envp)
{
	char	*s;
	struct	sigaction sa;
	struct	sigaction quit;
	t_token *tokens;
    t_token *current;
    t_node	*tree;
    t_node	*root;
    
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
			tree = createnode();
    		root = tree;
			inittree(&tree, current, envp);
			tree = root;
			//cleantree(&(tree));
			//tree = root;
			//traverse_tree(&root, envp);
			if (execute(root, envp) == 2)
			{
				ft_heredoc(root->left, envp);
			}
		 	//printTree(root);
		}
		if (s == NULL)
		{	
			rl_clear_history();
			exit(0);
		}
		free(s);
	}          
}                
